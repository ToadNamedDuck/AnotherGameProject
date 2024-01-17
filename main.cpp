//Written by Jason Harris - ToadNamedDuck. This is designed only for Windows at the moment.
#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include <iostream>
//Callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
};


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
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
	ShowWindow(window, nCmdShow);

	//Window message loop - user generated events to process via callback
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bool running = true;
	//Game loop
	return 0;
}