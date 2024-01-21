//Written by Jason Harris - ToadNamedDuck. This is designed only for Windows at the moment.
#ifndef UNICODE
#define UNICODE
#endif 
#include <iostream>
#include <windows.h>
#include "delta_time.cpp"
#include "tile.cpp"

bool running = true;


//Callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			running = false;
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};


int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	uint16_t testMask[16] = {
	0b0110110110110110,
	0b0110110110110110,
	0b1111111111111111,
	0b1111111111111111,
	0b0110110110110110,
	0b0110110110110110,
	0b1111111111111111,
	0b1111111111111111,
	0b0110110110110110,
	0b0110110110110110,
	0b1111111111111111,
	0b1111111111111111,
	0b0110110110110110,
	0b0110110110110110,
	0b1111111111111111,
	0b1111111111111111
	};
	Tile testTile(16, 0, 16, testMask);
	testTile.tell();
	testTile.showMask();
	//Register window class
	const wchar_t CLASS_NAME[] = L"Simple Window";
	WNDCLASS wnd = {};//Convert to WNDCLASSEX when I want icons. Need a 32x32 and a 16x16 .ico file.
	wnd.lpfnWndProc = WindowProc;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = CLASS_NAME;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wnd);

	//Create the window
	HWND window = CreateWindowEx(
		0,//optional Window styles
		CLASS_NAME,//window class
		L"Temp Window Name",//Window text (top of display bar)
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,//Window style
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,//Size, Pos
		NULL,//Parent window
		NULL,//Menu
		hInstance,//instance handle
		NULL//Additional app data
		);

	if (window == NULL)
	{
		return 0;
	}

	HDC deviceContext = GetDC(window);

	ShowWindow(window, nCmdShow);
	DeltaTime dt;
	dt.SetFrameBegin();
	//Game loop for now will incorporate the message loop.
	while (running)
	{
		//Window message loop - user generated events to process via callback
		MSG msg = {};
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		dt.ChangeDeltaTime();
	}

	return 0;
}