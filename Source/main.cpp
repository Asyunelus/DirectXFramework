#include "stdafx.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "ShopScene.h"
#include "GameScene.h"
#include "EndingScene.h"

VOID PrepareScenes() {
	SceneManager::GetInstance()->AddScene("Intro", new IntroScene);
	SceneManager::GetInstance()->AddScene("Game", new GameScene);
	SceneManager::GetInstance()->AddScene("Shop", new ShopScene);
	SceneManager::GetInstance()->AddScene("Game", new GameScene);
	SceneManager::GetInstance()->AddScene("Ending", new EndingScene);
	SceneManager::GetInstance()->ChangeScene("Game");
}

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL,
		CLASS_NAME, NULL
    };
    RegisterClassEx( &wc );

	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

    // Create the application's window
    HWND hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME,
                              WS_POPUP, 0, 0, ScreenWidth, ScreenHeight,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
	if (SUCCEEDED(DirectX::GetInstance()->InitD3D(hWnd, hInst, ScreenWidth, ScreenHeight)))
	{
		PrepareScenes();

		// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				DirectX::GetInstance()->OnTick();
		}
	}

	DirectX::GetInstance()->End();

    UnregisterClass( CLASS_NAME, wc.hInstance );
    return 0;
}
