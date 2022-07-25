//
//  SpriteFactory.cpp
//  BallTestVulkan
//
//  Created by Kelson Hootman on 7/17/22.
//  Copyright © 2022 Kelson Hootman. All rights reserved.
//

#include "SpriteFactory.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "StringHash.h"
#include "VulkanCore.h"
#include <string>
#include <cmath>
#include <assert.h>

void SpriteFactory::Init(KEngineVulkan::ShaderFactory * shaderFactory, KEngineVulkan::TextureFactory * textureFactory)
{
    mShaderFactory = shaderFactory;
	mTextureFactory = textureFactory;
	KEngineVulkan::DataLayout::AttributeBindingLayout attributes;
#ifdef NDEBUG
	assert(false);
#endif

	KEngineVulkan::DataLayout::AttributeBindingLayout::AttributeLayout positionAttribute{ HASH("Position", 0xBF5A86A3), KEngineVulkan::DataLayout::DataType::Vec4Float, 0 };
	KEngineVulkan::DataLayout::AttributeBindingLayout::AttributeLayout colorAttribute{ HASH("VertexColor", 0x65476198), KEngineVulkan::DataLayout::DataType::Vec4Float, 1 };
	KEngineVulkan::DataLayout::AttributeBindingLayout::AttributeLayout textureAttribute{ HASH("TextureCoordinates", 0x2E1BFB9A), KEngineVulkan::DataLayout::DataType::Vec2Float, 2 };
	attributes.attributes.push_back(positionAttribute);
	attributes.attributes.push_back(colorAttribute);
	attributes.attributes.push_back(textureAttribute);

	KEngineVulkan::DataLayout::UniformBindingLayout::UniformBufferFieldLayout modelUniformLayout{ HASH("ModelMatrix", 0xCD780745), KEngineVulkan::DataLayout::DataType::Mat4Float };
	KEngineVulkan::DataLayout::UniformBindingLayout::UniformBufferFieldLayout projectionUniformLayout{ HASH("ProjectionMatrix", 0x8E67F662), KEngineVulkan::DataLayout::DataType::Mat4Float };
	KEngineVulkan::DataLayout::UniformBindingLayout::UniformBufferFieldLayout{};
	KEngineVulkan::DataLayout::UniformBindingLayout uniforms{ true, false, false, false, {modelUniformLayout, projectionUniformLayout} };
	KEngineVulkan::DataLayout::UniformBindingLayout texture{ false, true, true, false, {} };

	mNoTextureLayout.Init(shaderFactory->GetCore(), { attributes }, { uniforms });
	mTextureLayout.Init(shaderFactory->GetCore(), { attributes }, { uniforms, texture });

	shaderFactory->CreatePipeline(HASH("Rainball", 0x036F6C7A), "basic.vert", "circlecolor.frag", mNoTextureLayout, true); //TODO:  find some way to associate the layout with the pipeline so mismatches don't occur
	shaderFactory->CreatePipeline(HASH("Textured", 0xDF225E87), "basic.vert", "textured.frag", mTextureLayout, false);
	textureFactory->CreateTexture(HASH("Smile", 0xC34B2C0B), "smile.png");
}

const KEngineVulkan::Sprite * SpriteFactory::BallSpriteForRadius(float radius)
{
    assert(mShaderFactory != nullptr);
    float diameter = round(radius * 2);
    if (mBallSprites.find(diameter) == mBallSprites.end()) {

        const Vertex Vertices[] = {
            {{diameter, 0, 0, 1}, {1, 0, 0, 1}, {1,0}},
            {{diameter, diameter, 0, 1}, {0, 1, 0, 1}, {1,1}},
            {{0, diameter, 0, 1}, {0, 0, 1, 1}, {0,1}},
            {{0, 0, 0, 1}, {0, 0, 0, 1}, {0,0}}
        };
        
        const uint16_t Indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        
		KEngineVulkan::Sprite & sprite = mBallSprites[diameter];
        sprite.width = sprite.height = diameter;
        
		KEngineVulkan::VulkanCore* core = mShaderFactory->GetCore();
		core->uploadVertexBuffer(Vertices, 4, sprite.vertexBuffer.first, sprite.vertexBuffer.second);
		core->uploadIndexBuffer(Indices, 6, sprite.indexBuffer.first, sprite.indexBuffer.second);
		sprite.graphicsPipeline = mShaderFactory->GetGraphicsPipeline(HASH("Rainball", 0x036F6C7A));
		sprite.mLayout = &mNoTextureLayout; //Should be associated with the pipeline, not manually selected here!
        sprite.indexCount = 6;
    }
    return &mBallSprites[diameter];
}

const KEngineVulkan::Sprite * SpriteFactory::BoxSpriteForDimensions(float width, float height)
{
	assert(mShaderFactory != nullptr);
	int roundWidth = round(width);
	int roundHeight = round(height);
	auto id = std::pair<int, int>(roundWidth, roundHeight);
	if (mBoxSprites.find(id) == mBoxSprites.end()) {
		const Vertex Vertices[] = {
			{ { roundWidth, 0, 0, 1 },{ 1, 1, 1, 1 },{ 1,0 } },
			{ { roundWidth, roundHeight, 0, 1 },{ 1, 1, 1, 1 },{ 1,1 } },
			{ { 0, roundHeight, 0, 1 },{ 1, 1, 1, 1 },{ 0,1 } },
			{ { 0, 0, 0, 1 },{ 1, 1, 1, 1 },{ 0,0 } }
		};

		const uint16_t Indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		KEngineVulkan::Sprite & sprite = mBoxSprites[id];
		sprite.width = roundWidth;
		sprite.height = roundHeight;

		KEngineVulkan::VulkanCore* core = mShaderFactory->GetCore();
		core->uploadVertexBuffer(Vertices, 4, sprite.vertexBuffer.first, sprite.vertexBuffer.second);
		core->uploadIndexBuffer(Indices, 6, sprite.indexBuffer.first, sprite.indexBuffer.second);
		sprite.graphicsPipeline = mShaderFactory->GetGraphicsPipeline(HASH("Textured", 0xDF225E87));
		sprite.mLayout = &mTextureLayout; //Should be associated with the pipeline, not manually selected here!
		sprite.indexCount = 6;
		sprite.textureImageView = mTextureFactory->GetTexture(HASH("Smile", 0xC34B2C0B));
		sprite.textureSampler = core->getSampler(false);
	}
	return &mBoxSprites[id];
}
