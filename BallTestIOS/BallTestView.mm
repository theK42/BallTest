//
//  BallTestView.m
//  BallTestIOS
//
//  Created by Kelson Hootman on 11/24/17.
//  Copyright © 2017 Kelson Hootman. All rights reserved.
//

#import "BallTestView.h"

@implementation BallTestView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES3;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 3.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, _colorRenderBuffer);
}

- (void)update:(CADisplayLink*)displayLink {
    CFTimeInterval previousTime = displayLink.timestamp;
    CFTimeInterval currentTime = displayLink.targetTimestamp;
    CFTimeInterval elapsedTimeInSeconds = currentTime - previousTime;
    timer.Update(elapsedTimeInSeconds);
    luaScheduler.Update();
    boxWorld.Update(elapsedTimeInSeconds);
    hierarchySystem.Update(elapsedTimeInSeconds);
    renderer.Render();
    
    
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        
        luaScheduler.Init();
        timer.Init(&luaScheduler);
        boxWorld.Init();
        hierarchySystem.Init();
        shaderFactory.Init();
        textureFactory.Init();
        spriteFactory.Init(&shaderFactory, &textureFactory);
        double width = frame.size.width;
        double height = frame.size.height;
        renderer.Init(width, height);
        
        
        boxWorld.AddWall({0, 0}, {width, 0}, {0, -50});
        boxWorld.AddWall({width, 0}, {width, height}, {50, 0});
        boxWorld.AddWall({width, height}, {0, height}, {0, 50});
        boxWorld.AddWall({0, height}, {0, 0}, {-50, 0});
        
        westBorder.Init(1.0f, 0.0f, 0.0f); //x = 0
        eastBorder.Init(-1.0f, 0.0f, frame.size.width); //-x + WIDTH = 0
        northBorder.Init(0.0f, 1.0f, 0.0f); // y = 0
        southBorder.Init(0.0f, -1.0f, frame.size.height); //-y + HEIGHT = 0
        
        rendererBinding.Init(luaScheduler.GetMainState(), &renderer);
        
        ballBinding.Init(luaScheduler.GetMainState(), &boxWorld, &hierarchySystem, &renderer, &spriteFactory);
        
        mainThread.Init(&luaScheduler, "script", true);
        
        [self setupDisplayLink];
    }
    return self;
}

// Replace dealloc method with this
- (void)dealloc
{
    _context = nil;
}

@end

