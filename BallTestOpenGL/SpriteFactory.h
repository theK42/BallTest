//
//  SpriteFactory.h
//  BallTestIOS
//
//  Created by Kelson Hootman on 11/26/17.
//  Copyright © 2017 Kelson Hootman. All rights reserved.
//

#pragma once

#include "SpriteRenderer.h"
#include <map>

namespace KEngineOpenGL {
    class ShaderFactory;
	class TextureFactory;
}

class SpriteFactory
{
public:
    void Init(KEngineOpenGL::ShaderFactory* shaderFactory, KEngineOpenGL::TextureFactory* textureFactory);
    const KEngineOpenGL::Sprite* BallSpriteForRadius(float radius);
	const KEngineOpenGL::Sprite* BoxSpriteForDimensions(float width, float height);
private:
    std::map<int, KEngineOpenGL::Sprite> mBallSprites;
	std::map<std::pair<int, int>, KEngineOpenGL::Sprite> mBoxSprites;
    bool  mInitialized {false};
    
    KEngineOpenGL::ShaderFactory * mShaderFactory;
	KEngineOpenGL::TextureFactory * mTextureFactory;
};

