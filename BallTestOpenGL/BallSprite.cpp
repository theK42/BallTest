//
//  BallSprite.cpp
//  BallTestIOS
//
//  Created by Kelson Hootman on 11/26/17.
//  Copyright © 2017 Kelson Hootman. All rights reserved.
//

#include "stdafx.h"
#include "BallSprite.h"
#include "OpenGLUtils.h"
#include "ShaderFactory.h"
#include "StringHash.h"
#include <string>
#include <cmath>
#include <assert.h>

void BallSpriteFactory::Init(KEngineOpenGL::ShaderFactory * shaderFactory)
{
    mShaderFactory = shaderFactory;
    shaderFactory->CreateShaderProgram(HASH("Rainball", 0x036F6C7A), "basic.vertex", "circlecolor.fragment");
}

const KEngineOpenGL::Sprite * BallSpriteFactory::BallSpriteForRadius(float radius)
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
    }
    return &mBallSprites[diameter];
}
