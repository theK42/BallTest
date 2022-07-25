// BallTestVulkan.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "BallTestVulkan.h"
#include "SpriteRenderer.h"
#include "StaticTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Boundaries2D.h"
#include "SimpleBall.h"
#include "RendererLuaBinding.h"
#include "BallLuaBinding.h"
#include "LuaScheduler.h"
#include "Timer.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "SpriteFactory.h"
#include "Box2DTransform.h"
#include "VulkanCore.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int, int, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BALLTESTVULKAN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    int width = 800;
    int height = 600;
    // Perform application initialization:
    HWND hWnd = InitInstance(hInstance, nCmdShow, width + 10, height + 50);
    if (!hWnd)
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BALLTESTVULKAN));

    HDC hDC = GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    int pf = ChoosePixelFormat(hDC, &pfd);
    if (!pf)
    {
        return 0;
    }

    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    SetPixelFormat(hDC, pf, &pfd);


    KEngineCore::LuaScheduler       luaScheduler;
    KEngineCore::Timer              timer;
    KEngine2D::HierarchyUpdater     hierarchySystem;

    KEngineBox2D::Box2DWorld		box2dWorld;

    KEngineVulkan::VulkanCore		core;
    KEngineVulkan::SpriteRenderer   renderer;
    KEngineVulkan::ShaderFactory    shaderFactory;
    KEngineVulkan::TextureFactory	textureFactory;
    SpriteFactory					spriteFactory;

    KEngine2D::RendererBinding      rendererBinding;
    BallLuaBinding                  ballBinding;
    KEngineCore::ScheduledLuaThread mainThread;

    KEngine2D::BoundaryLine westBorder;
    KEngine2D::BoundaryLine eastBorder;
    KEngine2D::BoundaryLine northBorder;
    KEngine2D::BoundaryLine southBorder;


    luaScheduler.Init();
    timer.Init(&luaScheduler);
    hierarchySystem.Init();
    core.Init("Ball Test Vulkan", hWnd, hInstance);
    shaderFactory.Init(&core);
    textureFactory.Init(&core);

    spriteFactory.Init(&shaderFactory, &textureFactory);
    renderer.Init(&core, width, height);//frame.size.width, frame.size.height);

    rendererBinding.Init(luaScheduler.GetMainState(), &renderer);

    box2dWorld.Init({ 0,9.8 });
    box2dWorld.AddWall({ 0.0f,0.0f }, { (double)width,0.0f }, { 0, -50 });
    box2dWorld.AddWall({ (double)width,0 }, { (double)width,(double)height }, { 50, 0 });
    box2dWorld.AddWall({ (double)width, (double)height }, { 0,(double)height }, { 0, 50 });
    box2dWorld.AddWall({ 0,(double)height }, { 0,0 }, { -50, 0 });


    ballBinding.Init(luaScheduler.GetMainState(), &box2dWorld, &hierarchySystem, &renderer, &spriteFactory);

    mainThread.Init(&luaScheduler, "script", true);


    DWORD previousTime = GetTickCount();


    MSG msg;
    memset(&msg, 0, sizeof(msg));

    while (msg.message != WM_QUIT) // 
    {
        if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            DWORD currentTime = GetTickCount();
            DWORD elapsedTime = currentTime - previousTime;
            previousTime = currentTime;
            double elapsedTimeInSeconds = elapsedTime / 1000.0f;
            timer.Update(elapsedTimeInSeconds);
            luaScheduler.Update();
            box2dWorld.Update(elapsedTimeInSeconds);
            hierarchySystem.Update(elapsedTimeInSeconds);
            renderer.Render();
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BALLTESTVULKAN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BALLTESTVULKAN);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
       CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return 0;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return hWnd;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
