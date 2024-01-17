#include <windows.h>
//Callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	//Create & register window class
	const wchar_t CLASS_NAME[] = L"Simple Window";
	WNDCLASS wnd = {};//Convert to WNDCLASSEX when I want icons. Need a 32x32 and a 16x16 .ico file.
	wnd.lpfnWndProc = WindowProc;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = CLASS_NAME;
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wnd);

	bool running = true;
	//Game loop
}