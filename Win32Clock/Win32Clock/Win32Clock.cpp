// Win32Clock.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Clock.h"

#define MAX_LOADSTRING 100
#define ID_TIMER 1
#define TWOPT (2*3.141592653)

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
TCHAR now_time[20];

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void SetInsotropic(HDC hdc, int cxClient, int cyClient);
void RotatePoint(POINT pt[], int nNum, int nAngle);
void DrawClock(HDC hdc);
void DrawHand(HDC hdc, SYSTEMTIME *pst, BOOL isChange, int tag);
BOOL isChange(SYSTEMTIME st, SYSTEMTIME stPrevious);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32CLOCK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32CLOCK));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32CLOCK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32CLOCK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hdc;
	SYSTEMTIME st;
	static SYSTEMTIME stPrevious;
	BOOL is_Change;
	static int cxClient, cyClient;
	static HBRUSH hBrushRed;
	RECT rt;
	TCHAR hour[5], minute[5], second[5];

	switch (message)
    {
	case WM_CREATE:
		{
			hdc = GetDC(hWnd);
			hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
			SetTimer(hWnd, ID_TIMER, 1000, NULL);
			GetLocalTime(&st);
			stPrevious = st;
			break;
		}
	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			break;
		}
	case WM_TIMER:
		{
			GetLocalTime(&st);
			is_Change = isChange(st, stPrevious);
			// 重画
			hdc = GetDC(hWnd);
			// 设置坐标系等元素
			SetInsotropic(hdc, cxClient, cyClient);
			// 使用白色画笔清空
			SelectObject(hdc, GetStockObject(WHITE_PEN));
			DrawHand(hdc, &stPrevious, is_Change, 0);

			SelectObject(hdc, GetStockObject(BLACK_PEN));
			// 选择黑色画刷重画
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, -153, -507, now_time, lstrlen(now_time));
			SetTextColor(hdc, RGB(255, 255, 255));
			TextOut(hdc, -160, -500, now_time, lstrlen(now_time));
			SetTextColor(hdc, RGB(0, 0, 0));
			DrawHand(hdc, &st, TRUE, 1);
			DrawClock(hdc);
			ReleaseDC(hWnd, hdc);
			stPrevious = st;
			break;
		}
	case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
			SetInsotropic(hdc, cxClient, cyClient);
			GetLocalTime(&st);
			GetClientRect(hWnd, &rt);

			HPEN pen1 = CreatePen(PS_SOLID, 120, RGB(0, 0, 0));
			HPEN oldPen1 = (HPEN)SelectObject(hdc, pen1);
			Ellipse(hdc, -1060, -1060, 1060, 1060);
			SelectObject(hdc, oldPen1);
			DeleteObject(pen1);

			// 为表盘添加阴影
			for (size_t i = 0; i < 100; i+=2)
			{
				HPEN pen = CreatePen(PS_SOLID, 1, RGB(140 + i, 140 + i, 140 + i));
				HPEN oldPen = (HPEN)SelectObject(hdc, pen);
				Ellipse(hdc, -1000 + i / 2, -1000 + i / 2, 1000 - i / 2, 1000 - i / 2);
				SelectObject(hdc, oldPen);
				DeleteObject(pen);
			}

			DrawClock(hdc);
			DrawHand(hdc, &stPrevious, TRUE, 1);
			wsprintf(hour, _T("%d"), st.wHour);
			wsprintf(minute, _T("%d"), st.wMinute);
			wsprintf(second, _T("%d"), st.wSecond);
			wsprintf(now_time, _T("%s:%s:%2s"), hour, minute, second);
			SetTextColor(hdc, RGB(0, 0, 0));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		KillTimer(hWnd, ID_TIMER);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
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

void SetInsotropic(HDC hdc, int cxClient, int cyClient)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 1200, 1200, NULL);
	SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
	SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
}

void RotatePoint(POINT pt[], int nNum, int nAngle)
{
	// 时针长度600 分针长度800 秒针长度800
	POINT pt_temp;
	for (size_t i = 0; i < nNum; i++)
	{
		pt_temp.x = (pt[i].x * cos(TWOPT * nAngle / 360) + pt[i].y * sin(TWOPT * nAngle / 360));
		pt_temp.y = (pt[i].y * cos(TWOPT * nAngle / 360) - pt[i].x * sin(TWOPT * nAngle / 360));
		pt[i] = pt_temp;
	}
}

void DrawClock(HDC hdc)
{
	WCHAR szBuffer[10];
	POINT pt[3];
	POINT pt_new;
	for (size_t i = 0; i < 360; i+=6)
	{
		pt[0].x = 0;
		pt[0].y = 900;

		RotatePoint(pt, 1, i);

		pt[2].x = pt[2].y = i % 5 ? 33 : 100;

		pt_new.x = pt[0].x - 100 * sin(TWOPT * i / 360);
		pt_new.y = pt[0].y - 100 * cos(TWOPT * i / 360);

		pt[0].x = pt[0].x - pt[2].x / 2;
		pt[0].y = pt[0].y - pt[2].y / 2;

		pt[1].x = pt[0].x + pt[2].x;
		pt[1].y = pt[0].y + pt[2].y;

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		Ellipse(hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);

		if (i % 5 == 0)
		{
			wsprintf(szBuffer, _T("%d"), (i / 30 == 0) ? 12 : i/30);
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, pt_new.x - 30, pt_new.y + 36, szBuffer, lstrlen(szBuffer));
		}
	}
}

void DrawHand(HDC hdc, SYSTEMTIME * pst, BOOL ifChange, int tag)
{
	// 时针长度600 分针长度800 秒针长度800
	static POINT pt[3][5] = {
		0, -150, 70, 0, 0, 600, -70, 0, 0, -150,
		0, -200, 40, 0, 0, 800, -40, 0, 0, -200,
		0, 0, -5, 0, -5, 800, 5, 800, 5, 0};

	int nAngle[3];
	POINT pt_tmp[3][5];
	POINT pt_shadow[3][5];
	WCHAR hour[4], minute[4], second[4];

	nAngle[0] = (pst->wHour * 30) % 360 + pst->wMinute / 2;
	nAngle[1] = (pst->wMinute * 6) + pst->wSecond / 10;
	nAngle[2] = (pst->wSecond * 6);

	memcpy(pt_tmp, pt, sizeof(pt));

	for (size_t i = 0; i < 3; i++)
	{
		RotatePoint(pt_tmp[i], 5, nAngle[i]);
	}

	memcpy(pt_shadow, pt_tmp, sizeof(pt_tmp));
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			pt_shadow[i][j].x += 16;
			pt_shadow[i][j].y += 16;
		}
	}

	if (tag == 1)
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 200));
		HPEN pen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, hBrush);
		SelectObject(hdc, pen);
		for (size_t i = 0; i < 3; i++)
		{
			Polygon(hdc, pt_shadow[i], 5);
		}
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		DeleteObject(hBrush);
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		for (size_t i = 0; i < 3; i++)
		{
			Polygon(hdc, pt_tmp[i], 5);
		}
	}
	else
	{
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		for (size_t i = 0; i < 3; i++)
		{
			Polygon(hdc, pt_shadow[i], 5);
		}
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		for (size_t i = 0; i < 3; i++)
		{
			Polygon(hdc, pt_tmp[i], 5);
		}
	}
	wsprintf(hour, _T("%02d"), pst->wHour);
	wsprintf(minute, _T("%02d"), pst->wMinute);
	wsprintf(second, _T("%02d"), pst->wSecond);
	wsprintf(now_time, _T("%s:%s:%s"), hour, minute, second);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(200, 200, 200));
	TextOut(hdc, -153, -507, now_time, lstrlen(now_time));
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, -160, -500, now_time, lstrlen(now_time));
}

BOOL isChange(SYSTEMTIME st, SYSTEMTIME stPrevious)
{
	return ((st.wHour != stPrevious.wHour) || (st.wMinute != stPrevious.wMinute) 
		|| (st.wSecond != stPrevious.wSecond));
}
