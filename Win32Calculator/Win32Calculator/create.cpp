#include "create.h"
#include "stdafx.h"

//创建计算器界面
void Create(HWND &hWnd, HWND &screen_hwnd_main, HWND &screen_hwnd_sub, HWND &btn_hwnd_ce, HWND &btn_hwnd_dot, HWND &btn_hwnd_equals, 
	HWND &btn_hwnd_minus, HWND &btn_hwnd_mod, HWND &btn_hwnd_over, HWND &btn_hwnd_plus, HWND &btn_hwnd_sqrt, HWND &btn_hwnd_times, HWND *btn_hwnd, HINSTANCE &hInst)
{
	//按键字体
	static HFONT hFont_Button = CreateFont(
		-30, -15, 0, 0, 400, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Consolas")
		);
	//主屏幕字体
	static HFONT hFont_MainScreen = CreateFont(
		-54, -27, 0, 0, 400,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Consolas")
		);
	//辅屏幕字体
	static HFONT hFont_SubScreen = CreateFont(
		-18, -9, 0, 0, 400,
		FALSE, FALSE, FALSE,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE, _T("Consolas")
		);

	//主屏幕
	screen_hwnd_main = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_RIGHT, _T("Static"), _T("0"),
		WS_VISIBLE | WS_CHILD, 10, 10, 380, 30, hWnd, (HMENU)SCREEN_ID_MAIN, hInst, NULL
		);
	//辅屏幕
	screen_hwnd_sub = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_RIGHT, _T("Static"), _T("0"),
		WS_VISIBLE | WS_CHILD, 10, 10, 380, 30, hWnd, (HMENU)SCREEN_ID_SUB, hInst, NULL
		);
	//创建按键
	btn_hwnd_ce = CreateWindow(_T("Button"), _T("AC"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 130, 95, 95, hWnd, (HMENU)BTN_ID_CLEAR, hInst, NULL);
	btn_hwnd_sqrt = CreateWindow(_T("Button"), _T("√"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 130, 95, 95, hWnd, (HMENU)BTN_ID_SQRT, hInst, NULL);
	btn_hwnd_mod = CreateWindow(_T("Button"), _T("Mod"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 130, 95, 95, hWnd, (HMENU)BTN_ID_MOD, hInst, NULL);
	btn_hwnd_plus = CreateWindow(_T("Button"), _T("+"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 295, 130, 95, 95, hWnd, (HMENU)BTN_ID_PLUS, hInst, NULL);

	btn_hwnd[7] = CreateWindow(_T("Button"), _T("7"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 225, 95, 95, hWnd, (HMENU)BTN_ID_7, hInst, NULL);
	btn_hwnd[8] = CreateWindow(_T("Button"), _T("8"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 225, 95, 95, hWnd, (HMENU)BTN_ID_8, hInst, NULL);
	btn_hwnd[9] = CreateWindow(_T("Button"), _T("9"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 225, 95, 95, hWnd, (HMENU)BTN_ID_9, hInst, NULL);
	btn_hwnd_minus = CreateWindow(_T("Button"), _T("-"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 295, 225, 95, 95, hWnd, (HMENU)BTN_ID_MINUS, hInst, NULL);

	btn_hwnd[4] = CreateWindow(_T("Button"), _T("4"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 320, 95, 95, hWnd, (HMENU)BTN_ID_4, hInst, NULL);
	btn_hwnd[5] = CreateWindow(_T("Button"), _T("5"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 320, 95, 95, hWnd, (HMENU)BTN_ID_5, hInst, NULL);
	btn_hwnd[6] = CreateWindow(_T("Button"), _T("6"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 320, 95, 95, hWnd, (HMENU)BTN_ID_6, hInst, NULL);
	btn_hwnd_times = CreateWindow(_T("Button"), _T("x"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 295, 320, 95, 95, hWnd, (HMENU)BTN_ID_TIMES, hInst, NULL);

	btn_hwnd[1] = CreateWindow(_T("Button"), _T("1"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 415, 95, 95, hWnd, (HMENU)BTN_ID_1, hInst, NULL);
	btn_hwnd[2] = CreateWindow(_T("Button"), _T("2"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 105, 415, 95, 95, hWnd, (HMENU)BTN_ID_2, hInst, NULL);
	btn_hwnd[3] = CreateWindow(_T("Button"), _T("3"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 415, 95, 95, hWnd, (HMENU)BTN_ID_3, hInst, NULL);
	btn_hwnd_over = CreateWindow(_T("Button"), _T("/"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 295, 415, 95, 95, hWnd, (HMENU)BTN_ID_OVER, hInst, NULL);

	btn_hwnd[0] = CreateWindow(_T("Button"), _T("0"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 10, 510, 190, 95, hWnd, (HMENU)BTN_ID_0, hInst, NULL);
	btn_hwnd_dot = CreateWindow(_T("Button"), _T("."), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 510, 95, 95, hWnd, (HMENU)BTN_ID_DOT, hInst, NULL);
	btn_hwnd_equals = CreateWindow(_T("Button"), _T("="), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 295, 510, 95, 95, hWnd, (HMENU)BTN_ID_EQUAL, hInst, NULL);

	SendMessage(screen_hwnd_main, WM_SETFONT, (WPARAM)hFont_MainScreen, NULL);
	SendMessage(screen_hwnd_sub, WM_SETFONT, (WPARAM)hFont_SubScreen, NULL);
	for (int i = 0; i < 10; i++)
	{
		SendMessage(btn_hwnd[i], WM_SETFONT, (WPARAM)hFont_Button, NULL);
	}
	SendMessage(btn_hwnd_ce, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_sqrt, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_mod, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_plus, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_minus, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_times, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_over, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_dot, WM_SETFONT, (WPARAM)hFont_Button, NULL);
	SendMessage(btn_hwnd_equals, WM_SETFONT, (WPARAM)hFont_Button, NULL);
}
