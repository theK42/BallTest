//
//  SpriteFactory.h
//  BallTestVulkan
//
//  Created by Kelson Hootman on 7/17/22.
//  Copyright © 2022 Kelson Hootman. All rights reserved.
//

#pragma once

#include "SpriteRenderer.h"
#include <map>

namespace KEngineVulkan {
    class ShaderFactory;
	class TextureFactory;
}

class SpriteFactory
{
public:
    void Init(KEngineVulkan::ShaderFactory* shaderFactory, KEngineVulkan::TextureFactory* textureFactory);
    const KEngineVulkan::Sprite* BallSpriteForRadius(float radius);
	const KEngineVulkan::Sprite* BoxSpriteForDimensions(float width, float height);
private:
    struct Vertex
    {
        float Position[4];
        float Color[4];
        float Texture[2];
    };

    std::map<int, KEngineVulkan::Sprite> mBallSprites;
	std::map<std::pair<int, int>, KEngineVulkan::Sprite> mBoxSprites;
    bool  mInitialized {false};
    
    KEngineVulkan::ShaderFactory * mShaderFactory;
    KEngineVulkan::TextureFactory * mTextureFactory;
    
	KEngineVulkan::DataLayout mNoTextureLayout{};
	KEngineVulkan::DataLayout mTextureLayout{};
};

