//
//  BallTestView.h
//  BallTestIOS
//
//  Created by Kelson Hootman on 11/24/17.
//  Copyright © 2017 Kelson Hootman. All rights reserved.
//

#ifndef BallTestView_h
#define BallTestView_h

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "SpriteRenderer.h"
#include "StaticTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Boundaries2D.h"
#include "Box2DTransform.h"
#include "SimpleBall.h"
#include "RendererLuaBinding.h"
#include "BallLuaBinding.h"
#include "LuaScheduler.h"
#include "Timer.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "SpriteFactory.h"

@interface BallTestView : UIView {
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
    /*GLint _positionSlot;
     GLint _colorSlot;
     GLuint _projectionUniform;*/
    
    KEngineCore::LuaScheduler       luaScheduler;
    KEngineCore::Timer              timer;
    KEngine2D::HierarchyUpdater     hierarchySystem;
    KEngineBox2D::Box2DWorld        boxWorld;
    KEngineOpenGL::SpriteRenderer   renderer;
    KEngineOpenGL::ShaderFactory    shaderFactory;
    KEngineOpenGL::TextureFactory   textureFactory;
    SpriteFactory                   spriteFactory;
    
    KEngine2D::RendererBinding      rendererBinding;
    BallLuaBinding                  ballBinding;
    KEngineCore::ScheduledLuaThread mainThread;
 
    KEngine2D::BoundaryLine westBorder;
    KEngine2D::BoundaryLine eastBorder;
    KEngine2D::BoundaryLine northBorder;
    KEngine2D::BoundaryLine southBorder;
    
}
@end
#endif /* BallTestView_h */
