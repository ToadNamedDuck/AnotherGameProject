//Written by Jason Harris - ToadNamedDuck. This is designed only for Windows at the moment.
#ifndef UNICODE
#define UNICODE
#endif 
#include <iostream>
#include <windows.h>
#include "delta_time.cpp"
#include "tile.cpp"

//Simple struct for handling the render state.
struct RenderState {
	int height;
	int width;
	void* memory;

	BITMAPINFO bitmapinfo;
};

RenderState renderState;
bool running = true;




//Callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		renderState.width = rect.right - rect.left;
		renderState.height = rect.bottom - rect.top;
		int render_state_size = renderState.width * renderState.height * sizeof(unsigned int);

		//Get a heap of memory from the operating system. Clear memory before getting it.
		if (renderState.memory) VirtualFree(renderState.memory, 0, MEM_RELEASE);

		renderState.memory = VirtualAlloc(0, render_state_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		renderState.bitmapinfo.bmiHeader.biSize = sizeof(renderState.bitmapinfo.bmiHeader);
		renderState.bitmapinfo.bmiHeader.biWidth = renderState.width;
		renderState.bitmapinfo.bmiHeader.biHeight = renderState.height;
		renderState.bitmapinfo.bmiHeader.biPlanes = 1;
		renderState.bitmapinfo.bmiHeader.biBitCount = 32;
		renderState.bitmapinfo.bmiHeader.biCompression = BI_RGB;
	} break;
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
	Tile testTile(16, 0, 0, testMask);
	testTile.tell();
	testTile.showMask();
	Pixel (&pixels)[16][16] = testTile.getPixels();
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			std::cout << pixels[x][y].r << " " << pixels[x][y].g << " " << pixels[x][y].b << " | ";
		}
		std::cout << std::endl;
	}
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
		//Simulate Game
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				SetPixel(deviceContext, x, y, RGB(pixels[x][y].r, pixels[x][y].g, pixels[x][y].b));
			}
		}
		StretchDIBits(deviceContext,
			0,
			0,
			renderState.width,
			renderState.height,
			0,
			0,
			renderState.width,
			renderState.height,
			renderState.memory,
			&renderState.bitmapinfo,
			DIB_RGB_COLORS, SRCCOPY);

		dt.ChangeDeltaTime();
	}

	return 0;
}