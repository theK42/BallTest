//
//  main.cpp
//  BallTestMac
//
//  Created by Kelson Hootman on 10/5/12.
//
//

#include <sys/time.h>

#include "CursesRenderer.h"
#include "StaticTransform2D.h"
#include "MechanicalTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Boundaries2D.h"
#include "Physics2D.h"
#include "SimpleBall.h"
#include "RendererLuaBinding.h"
#include "BallLuaBinding.h"
#include "LuaScheduler.h"
#include "Timer.h"

#define WIDTH 80
#define HEIGHT 25

long GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (long)(tv.tv_sec*1000 + (tv.tv_usec / 1000));
}

int main(int argc, const char * argv[])
{	
	KEngineCore::LuaScheduler		luaScheduler;
	KEngineCore::Timer				timer;
	KEngine2D::HierarchyUpdater		hierarchySystem;
	KEngine2D::MechanicsUpdater		mechanicsSystem;
	KEngine2D::PhysicsSystem		physicsSystem;
	KEngineCurses::CursesRenderer	renderer;

	luaScheduler.Init();
	timer.Init(&luaScheduler);
	mechanicsSystem.Init();
	physicsSystem.Init();
	hierarchySystem.Init();

	renderer.Init(WIDTH, HEIGHT);

	KEngine2D::BoundaryLine westBorder;
	westBorder.Init(1.0f, 0.0f, 0.0f); //x = 0
	physicsSystem.AddBoundary(&westBorder);
	KEngine2D::BoundaryLine eastBorder;
	eastBorder.Init(-1.0f, 0.0f, WIDTH); //-x + WIDTH = 0
	physicsSystem.AddBoundary(&eastBorder);
	KEngine2D::BoundaryLine northBorder;
	northBorder.Init(0.0f, 1.0f, 0.0f); // y = 0
	physicsSystem.AddBoundary(&northBorder);
	KEngine2D::BoundaryLine southBorder;
	southBorder.Init(0.0f, -1.0f, HEIGHT); //-y + HEIGHT = 0
	physicsSystem.AddBoundary(&southBorder);

	KEngine2D::RendererBinding rendererBinding;
	rendererBinding.Init(luaScheduler.GetMainState(), &renderer);

	BallLuaBinding ballBinding;
	ballBinding.Init(luaScheduler.GetMainState(), &mechanicsSystem, &physicsSystem, &hierarchySystem, &renderer);

	KEngineCore::ScheduledLuaThread mainThread;
	mainThread.Init(&luaScheduler, "script.lua", true);
	
	long previousTime = GetTickCount();
	while(true)
	{
		long currentTime = GetTickCount();
		long elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		float elapsedTimeInSeconds = elapsedTime / 1000.0f;
		timer.Update(elapsedTimeInSeconds);
		luaScheduler.Update();
		mechanicsSystem.Update(elapsedTimeInSeconds);
		hierarchySystem.Update(elapsedTimeInSeconds);
		physicsSystem.Update(elapsedTimeInSeconds);
		renderer.Render();
	}

	
    return 0;
}

