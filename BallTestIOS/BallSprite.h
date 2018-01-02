//
//  BallSprite.h
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
}

class SpriteFactory
{
public:
    void Init(KEngineOpenGL::ShaderFactory* shaderFactory);
    const KEngineOpenGL::Sprite* BallSpriteForRadius(float radius);
private:
    std::map<int, KEngineOpenGL::Sprite> mBallSprites;
    bool  mInitialized {false};
    GLint mBallShaderProgram;
    
    KEngineOpenGL::ShaderFactory * mShaderFactory;
};

