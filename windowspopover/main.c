// 9 october 2014
#define UNICODE
#define _UNICODE
#define STRICT
#define STRICT_TYPED_ITEMIDS
// get Windows version right; right now Windows XP
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#define _WIN32_WINDOWS 0x0501		/* according to Microsoft's winperf.h */
#define _WIN32_IE 0x0600			/* according to Microsoft's sdkddkver.h */
#define NTDDI_VERSION 0x05010000	/* according to Microsoft's sdkddkver.h */
#include <windows.h>
#include <commctrl.h>
#include <stdint.h>
#include <uxtheme.h>
#include <string.h>
#include <wchar.h>
#include <windowsx.h>
#include <vsstyle.h>
#include <vssym32.h>

HWND popover;

LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == 100) {
			MoveWindow(popover, 50, 50,  200, 200, TRUE);
			ShowWindow(popover, SW_SHOW);
			UpdateWindow(popover);
			return 0;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int main(int argc, char *argv[])
{
	WNDCLASSW wc;
	HWND mainwin, button;
	MSG msg;

	ZeroMemory(&wc, sizeof (WNDCLASSW));
	wc.lpszClassName = L"popover";
	wc.lpfnWndProc = DefWindowProcW;
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	wc.style = CS_DROPSHADOW | CS_NOCLOSE;
	if (RegisterClassW(&wc) == 0)
		abort();
	popover = CreateWindowExW(WS_EX_TOPMOST,
		L"popover", L"",
		WS_POPUP | WS_BORDER,
		0, 0, 150, 100,
		NULL, NULL, NULL, NULL);
	if (popover == NULL)
		abort();

	ZeroMemory(&wc, sizeof (WNDCLASSW));
	wc.lpszClassName = L"mainwin";
	wc.lpfnWndProc = wndproc;
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	if (RegisterClassW(&wc) == 0)
		abort();
	mainwin = CreateWindowExW(0,
		L"mainwin", L"Main Window",
		WS_OVERLAPPEDWINDOW,
		0, 0, 150, 100,
		NULL, NULL, NULL, NULL);
	if (mainwin == NULL)
		abort();
	button = CreateWindowExW(0,
		L"button", L"Click Me",
		BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
		20, 20, 100, 40,
		mainwin, (HMENU) 100, NULL, NULL);
	if (button == NULL)
		abort();
	ShowWindow(mainwin, SW_SHOWDEFAULT);
	if (UpdateWindow(mainwin) == 0)
		abort();
	while (GetMessageW(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
