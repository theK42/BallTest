// BallTestWindows.cpp : Defines the entry point for the console application.
//


#include <windows.h>
#include "ConsoleRenderer.h"
#include "StaticTransform2D.h"
#include "MechanicalTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Boundaries2D.h"
#include "Physics2D.h"
#include "SimpleBall.h"
#include "lua.hpp"
#include "RendererLuaBinding.h"
#include "BallLuaBinding.h"
#include "DirectInput.h"
#include "LuaScheduler.h"
#include "Timer.h"



#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>


#define WIDTH 80
#define HEIGHT 25


HWND GetConsoleHwnd();

int WINAPI WinMain(
  HINSTANCE hInstance,  // handle to current instance
  HINSTANCE hPrevInstance,  // handle to previous instance
  LPSTR lpCmdLine,      // pointer to command line
  int nCmdShow          // show state of window
) 
{
	AllocConsole();

	
	long lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	FILE *fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	std::ios::sync_with_stdio();


	KEngineCore::LuaScheduler		luaScheduler;
	KEngineCore::Timer				timer;
	KEngine2D::HierarchyUpdater		hierarchySystem;
	KEngine2D::MechanicsUpdater		mechanicsSystem;
	KEngine2D::PhysicsSystem		physicsSystem;
	KEngineWindows::ConsoleRenderer	renderer;
	KEngineWindows::DirectInput		input;

	
	luaScheduler.Init();
	timer.Init(&luaScheduler);
	mechanicsSystem.Init();
	physicsSystem.Init();
	hierarchySystem.Init();
	input.Init(&luaScheduler, hInstance, GetConsoleHwnd(), 0.5);

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
	mainThread.Init(&luaScheduler, "script", true);
		
	DWORD previousTime = GetTickCount();

	bool continueRunning = true;

	while(continueRunning)
	{
		DWORD currentTime = GetTickCount();
		DWORD elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		double elapsedTimeInSeconds = elapsedTime / 1000.0f;
		timer.Update(elapsedTimeInSeconds);
		luaScheduler.Update();
		mechanicsSystem.Update(elapsedTimeInSeconds);
		hierarchySystem.Update(elapsedTimeInSeconds);
		physicsSystem.Update(elapsedTimeInSeconds);
		renderer.Render();
	}

	Sleep(1000);
	return 0;
}


HWND GetConsoleHwnd(void)
{
    #define MY_BUFSIZE 1024 // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    wchar_t pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                        // WindowTitle.
    wchar_t pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                        // WindowTitle.

    // Fetch current window title.

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.

    wsprintf(pszNewWindowTitle,L"%d/%d",
                GetTickCount(),
                GetCurrentProcessId());

    // Change current window title.

    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.

    Sleep(40);

    // Look for NewWindowTitle.

    hwndFound=FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}
	