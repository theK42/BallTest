//
//  BallSprite.cpp
//  BallTestIOS
//
//  Created by Kelson Hootman on 11/26/17.
//  Copyright © 2017 Kelson Hootman. All rights reserved.
//

#include "stdafx.h"
#include "SpriteFactory.h"
#include "OpenGLUtils.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "StringHash.h"
#include <string>
#include <cmath>
#include <assert.h>

void SpriteFactory::Init(KEngineOpenGL::ShaderFactory * shaderFactory, KEngineOpenGL::TextureFactory * textureFactory)
{
    mShaderFactory = shaderFactory;
	mTextureFactory = textureFactory;
	shaderFactory->CreateShaderProgram(HASH("Rainball", 0x036F6C7A), "basic.vertex", "circlecolor.fragment");
	shaderFactory->CreateShaderProgram(HASH("Textured", 0xDF225E87), "basic.vertex", "textured.fragment");
	textureFactory->CreateTexture(HASH("Smile", 0xC34B2C0B), "smile.png");
}

const KEngineOpenGL::Sprite * SpriteFactory::BallSpriteForRadius(float radius)
{
    assert(mShaderFactory != nullptr);
    float diameter = round(radius * 2);
    if (mBallSprites.find(diameter) == mBallSprites.end()) {
        const KEngineOpenGL::Vertex Vertices[] = {
            {{diameter, 0, 0}, {1, 0, 0, 1}, {1,0}},
            {{diameter, diameter, 0}, {0, 1, 0, 1}, {1,1}},
            {{0, diameter, 0}, {0, 0, 1, 1}, {0,1}},
            {{0, 0, 0}, {0, 0, 0, 1}, {0,0}}
        };
        
        const GLushort Indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        KEngineOpenGL::Sprite & sprite = mBallSprites[diameter];
        sprite.width = sprite.height = diameter;
        
        //sprite.vertexBuffer = KEngineOpenGL::UploadVertices(Vertices, 4);
        //sprite.indexBuffer = KEngineOpenGL::UploadIndices(Indices, 6);
        sprite.vertexArrayObject = KEngineOpenGL::UploadModel(Vertices, 4, Indices, 6);
        sprite.shaderProgram = mShaderFactory->GetShaderProgram(HASH("Rainball", 0x036F6C7A));
        sprite.indexCount = 6;
		sprite.texture = 0; // no texture
    }
    return &mBallSprites[diameter];
}

const KEngineOpenGL::Sprite * SpriteFactory::BoxSpriteForDimensions(float width, float height)
{
	assert(mShaderFactory != nullptr);
	int roundWidth = round(width);
	int roundHeight = round(height);
	auto id = std::pair<int, int>(roundWidth, roundHeight);
	if (mBoxSprites.find(id) == mBoxSprites.end()) {
		const KEngineOpenGL::Vertex Vertices[] = {
			{ { roundWidth, 0, 0 },{ 1, 1, 1, 1 },{ 1,0 } },
			{ { roundWidth, roundHeight, 0 },{ 1, 1, 1, 1 },{ 1,1 } },
			{ { 0, roundHeight, 0 },{ 1, 1, 1, 1 },{ 0,1 } },
			{ { 0, 0, 0 },{ 1, 1, 1, 1 },{ 0,0 } }
		};

		const GLushort Indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		KEngineOpenGL::Sprite & sprite = mBoxSprites[id];
		sprite.width = roundWidth;
		sprite.height = roundHeight;

		sprite.vertexArrayObject = KEngineOpenGL::UploadModel(Vertices, 4, Indices, 6);
		sprite.shaderProgram = mShaderFactory->GetShaderProgram(HASH("Textured", 0xDF225E87));
		sprite.indexCount = 6;
		sprite.texture = mTextureFactory->GetTexture(HASH("Smile", 0xC34B2C0B));
	}
	return &mBoxSprites[id];
}
