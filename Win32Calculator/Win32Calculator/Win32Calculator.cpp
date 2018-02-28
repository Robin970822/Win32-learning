// Win32Calculator.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Calculator.h"
#include "create.h"
#include "operate.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND btn_hwnd[10];                              // 十个数字键
HWND btn_hwnd_dot,                              // .
btn_hwnd_plus,                                  // +
btn_hwnd_minus,									// -
btn_hwnd_times,									// *
btn_hwnd_over,									// /
btn_hwnd_equals;								// =
HWND btn_hwnd_ce;								// 清除
HWND btn_hwnd_mod;								// 取模
HWND btn_hwnd_sqrt;								// 根号
HWND screen_hwnd_main;							// 主屏幕
HWND screen_hwnd_sub;							// 辅屏幕
bool isEqual = false;							// 等号状态
wstring input1;								    // 符号输入

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 封装操作
void Calculate(WPARAM wParam, HWND hWnd);
void keyboard(char ch, HWND hWnd);

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
    LoadStringW(hInstance, IDC_WIN32CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32CALCULATOR));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32CALCULATOR);
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
   WNDCLASSEX wincl;
   wincl.hInstance = hInst;
   wincl.lpszClassName = CLASSNAME;
   wincl.lpfnWndProc = WndProc;
   wincl.style = CS_VREDRAW | CS_HREDRAW;
   wincl.cbSize = sizeof(WNDCLASSEX);
   wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
   wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
   wincl.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32CALCULATOR);  // 创建菜单
   wincl.cbClsExtra = 0;
   wincl.cbWndExtra = 0;
   wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
   if (!RegisterClassEx(&wincl))
   {
	   MessageBox(NULL, _T("Could not register the window class"), _T("ERROR"), MB_OK | MB_ICONERROR);
	   return 0;
   }


   HWND hWnd = CreateWindowEx(
	   0,
	   CLASSNAME,
	   _T("Calculator"),
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	   CW_USEDEFAULT,
	   CW_USEDEFAULT,
	   405,
	   665,
	   HWND_DESKTOP,
	   NULL,
	   hInst,
	   NULL);

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
    switch (message)
    {
	case WM_CREATE:
		// 绘制主界面
		Create(hWnd, screen_hwnd_main, screen_hwnd_sub, btn_hwnd_ce, btn_hwnd_dot,
			btn_hwnd_equals, btn_hwnd_minus, btn_hwnd_mod, btn_hwnd_over,
			btn_hwnd_plus, btn_hwnd_sqrt, btn_hwnd_times, btn_hwnd, hInst);
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		//MessageBox(NULL, NULL, TEXT("Create"), MB_OK);
		break;
	case WM_CHAR:
		{
			char ch = char(wParam);
			keyboard(ch, hWnd);
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
                break;
            }

			Calculate(wParam, hWnd);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

void Calculate(WPARAM wParam, HWND hWnd)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		wstring input;			// 数字输入

		switch (LOWORD(wParam))
		{
		case BTN_ID_0:
		{
			input += '0';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
			MessageBox(NULL, input.c_str(), input.c_str(), MB_OK);
		}
		break;
		case BTN_ID_1:
		{
			input += '1';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_2:
		{
			input += '2';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_3:
		{
			input += '3';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_4:
		{
			input += '4';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_5:
		{
			input += '5';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_6:
		{
			input += '6';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_7:
		{
			input += '7';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_8:
		{
			input += '8';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_9:
		{
			input += '9';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case BTN_ID_PLUS:
		{
			input1 = _T("+");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);

		}
		break;
		case BTN_ID_MINUS:
		{
			input1 = _T("-");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case BTN_ID_TIMES:
		{
			input1 = _T("*");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case BTN_ID_OVER:
		{
			input1 = _T("/");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case BTN_ID_MOD:
		{
			input1 = _T("%");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case BTN_ID_EQUAL:
		{
			// 状态转移
			isEqual = true;

			//wstring input3 = _T("=");
			Equal(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);

		}
		break;
		case BTN_ID_CLEAR:
		{
			SetFocus(hWnd);
			input1.clear();
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		case BTN_ID_DOT:
		{
			Dot(hWnd, screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		case BTN_ID_SQRT:
		{
			Sqrt(hWnd, screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		default:
			break;
		}
	}
}

void keyboard(char ch, HWND hWnd)
{
	if (true)
	{
		wstring input;			// 数字输入

		switch (ch)
		{
		case '0':
		{
			input += '0';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
			MessageBox(NULL, input.c_str(), input.c_str(), MB_OK);
		}
		break;
		case '1':
		{
			input += '1';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '2':
		{
			input += '2';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '3':
		{
			input += '3';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '4':
		{
			input += '4';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '5':
		{
			input += '5';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '6':
		{
			input += '6';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '7':
		{
			input += '7';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '8':
		{
			input += '8';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '9':
		{
			input += '9';
			Number(hWnd, screen_hwnd_main, screen_hwnd_sub, input, input1, isEqual);
		}
		break;
		case '+':
		{
			input1 = _T("+");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);

		}
		break;
		case '-':
		{
			input1 = _T("-");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case '*':
		{
			input1 = _T("*");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case '/':
		{
			input1 = _T("/");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case '%':
		{
			input1 = _T("%");
			Operator(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);
		}
		break;
		case '=':
		{
			// 状态转移
			isEqual = true;

			//wstring input3 = _T("=");
			Equal(hWnd, screen_hwnd_main, screen_hwnd_sub, input1, isEqual);

		}
		break;
		case 'c':
		{
			SetFocus(hWnd);
			input1.clear();
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		case '.':
		{
			Dot(hWnd, screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		case 's':
		{
			Sqrt(hWnd, screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		break;
		default:
			break;
		}
	}
}
