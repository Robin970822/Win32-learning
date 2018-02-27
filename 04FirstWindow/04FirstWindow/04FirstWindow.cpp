#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <math.h>

/*
定义
*/
#define ID_RESULT 20
#define ID_BUTTON0 0
#define ID_BUTTON1 1
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_BUTTON4 4
#define ID_BUTTON5 5
#define ID_BUTTON6 6
#define ID_BUTTON7 7
#define ID_BUTTON8 8
#define ID_BUTTON9 9
#define ID_BUTTON_PLUS 10
#define ID_BUTTON_MINUS 11
#define ID_BUTTON_MULTI 12
#define ID_BUTTON_DIVIDE 13
#define ID_BUTTON_POINT 14
#define ID_BUTTON_EQUAL 15
#define ID_BUTTON_MOD 16
#define ID_BUTTON_SQRT 17
#define ID_BUTTON_C 18

HINSTANCE hInst;//定义全局变量来保存实例句柄
//WNDPROC EditProc;
static HWND hwndResult;//编辑框窗口句柄
static std::string str;//保存当前输入的字符串
static int max = 0;//当前输入的数字长度
static int iFlag = 0;
static double minus1;
static double minus2;
static std::string str3;
static char op = ' ';
static char op1 = ' ';
static int continous = 0;
static int chujin = 0;

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ProcFloat(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
double getResult(std::string stri);
void doCalculate(char op, double fNum1, double fNum2);

int APIENTRY WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR  lpCmdLine,
					int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;

	hInst = hInstance;
	char szClassName[] = "MainWClass";
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//若大小改变则重画
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance,(LPSTR)IDI_ICON1);//IDI_APPLICATION
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);//(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = TEXT("MainWClass");
	wndclass.lpszMenuName = (LPSTR)IDR_MENU1;
	wndclass.hIconSm = NULL;

	RegisterClassEx(&wndclass);
	hwnd = CreateWindowEx(
		0,
		TEXT("MainWCLass"),
		TEXT("My First Window!"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		285,
		280,
		NULL,
		NULL,
		hInstance,
		NULL);
	if(hwnd == NULL)
	{
		MessageBox(NULL,TEXT("创建窗口出错"),TEXT("error"),MB_OK);
		return -1;
	}
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char szText[] = "计算器";
	//static int cxChar,cyChar;
	static std::string str1;//第一个操作数
	static std::string str2;//第二个操作数
	
	static double fNum1;//第一个数
	static double fNum2;//第二个数
	static double resultNum;//结果
	//static char op;//操作符

	switch(message)
	{
	case WM_CREATE:
		{
			SetWindowText(hwnd,"计算器");
			hwndResult = CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("edit"),NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_RIGHT,
					10,10,250,25,hwnd,(HMENU)ID_RESULT,((LPCREATESTRUCT)lParam)->hInstance,NULL);

			//创建各个按钮
			CreateWindow(TEXT("button"),TEXT("7"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,10,45,40,36,hwnd,(HMENU)ID_BUTTON7,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("8"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,59,45,40,36,hwnd,(HMENU)ID_BUTTON8,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("9"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,108,45,40,36,hwnd,(HMENU)ID_BUTTON9,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("Sqr"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,170,45,40,36,hwnd,(HMENU)ID_BUTTON_SQRT,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("C"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,215,45,40,36,hwnd,(HMENU)ID_BUTTON_C,hInst,NULL);

			CreateWindow(TEXT("button"),TEXT("4"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,10,85,40,36,hwnd,(HMENU)ID_BUTTON4,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("5"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,59,85,40,36,hwnd,(HMENU)ID_BUTTON5,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("6"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,108,85,40,36,hwnd,(HMENU)ID_BUTTON6,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("+"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,170,85,40,36,hwnd,(HMENU)ID_BUTTON_PLUS,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("-"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,215,85,40,36,hwnd,(HMENU)ID_BUTTON_MINUS,hInst,NULL);

			CreateWindow(TEXT("button"),TEXT("1"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,10,125,40,36,hwnd,(HMENU)ID_BUTTON1,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("2"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,59,125,40,36,hwnd,(HMENU)ID_BUTTON2,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("3"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,108,125,40,36,hwnd,(HMENU)ID_BUTTON3,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("*"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,170,125,40,36,hwnd,(HMENU)ID_BUTTON_MULTI,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("/"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,215,125,40,36,hwnd,(HMENU)ID_BUTTON_DIVIDE,hInst,NULL);

			CreateWindow(TEXT("button"),TEXT("0"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,10,165,90,36,hwnd,(HMENU)ID_BUTTON0,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("."),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,108,165,40,36,hwnd,(HMENU)ID_BUTTON_POINT,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("="),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,170,165,40,36,hwnd,(HMENU)ID_BUTTON_EQUAL,hInst,NULL);
			CreateWindow(TEXT("button"),TEXT("%"),BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,215,165,40,36,hwnd,(HMENU)ID_BUTTON_MOD,hInst,NULL);
			return 0;
		}
	case WM_SIZE:
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_RESULT://处理键盘操作
		{
			char numb[40] = "";
			GetWindowText(GetDlgItem(hwnd,LOWORD(wParam)),numb,40);//得到编辑框中的字符串
			str = numb;//将字符串交给存放变量str
			int flag = 0;
			int i = 0;
			for(i = 0; i < (int)str.length(); i++)
			{
				if(str.at(i)=='+' || str.at(i)=='-' || str.at(i)=='*' || str.at(i)=='/')
				{
					//用来标识是否有+-*/，如果有并且有等号，就会去处理计算，
					//将字符串str分割
					iFlag = 1;
				}
				if(str.at(i) == '=')
				{
					//只显示等号之前的部分
					SetWindowText(hwndResult,str.substr(0,str.length()-1).c_str());
					str = str.substr(0,str.length());
					goto l;
				}
			}
			break;
		}
		case ID_FILE_EXIT:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		case ID_COPY:
			MessageBox(NULL,TEXT("hahahah"),TEXT("hahaha"),MB_OK);
			break;
		case ID_PASTE:
			break;
		case ID_BUTTON1:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "1";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON2:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "2";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON3:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "3";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON4:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "4";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON5:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "5";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON6:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "6";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON7:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "7";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON8:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "8";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON9:
		{
			max++;
			if(max>40)
			{
				break;
			}
			else
			{
				str = str + "9";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
				break;
			}
		}
		case ID_BUTTON0:
			if(str == "0")
			{
				SetWindowText(hwndResult,"0");
				max = 0;
			}
			else
			{
				str = str + "0";
				max++;
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
			}
			break;
		case ID_BUTTON_POINT:
			for(int i = 0; i< (int)str.length();i++)
			{
				if(str.at(i) == '.')
				{
					break;
				}
				if(str.at(i) != '.' && i == str.length()-1){
					str = str + ".";
					max++;
					SetWindowText(hwndResult,(LPCSTR)str.c_str());
				}
			}
			break;
		case ID_BUTTON_C:
			SetWindowText(hwndResult,"0");
			str = "";
			str1 = "";
			str2 = "";
			op = ' ';
			chujin = 0;
			max = 0;
			break;
		case ID_BUTTON_PLUS:
		{
			if(op == ' ')
			{
				str1 = str;
				op = '+';
				max = 0;
				str = "";
			}
			else
			{
				str2 = str;
				doCalculate(op,std::atof(str1.c_str()),std::atof(str2.c_str()));
				str1 = str;
				str = "";
				op = '+';
			}
			break;
		}
		case ID_BUTTON_MOD:
		{
			if(op == ' ')
			{
				str1 = str;
				op = '%';
				max = 0;
				str = "";
			}
			else
			{
				str2 = str;
				doCalculate(op,std::atof(str1.c_str()),std::atof(str2.c_str()));
				str1 = str;
				str = "";
				op = '%';
			}
			break;
		}
		case ID_BUTTON_MINUS:
		{
			if(str == "")
			{
				str = str+"-";
				SetWindowText(hwndResult,(LPCSTR)str.c_str());
			}
			else
			{
				if(op == ' ')
				{
					str1 = str;
					op = '-';
					max = 0;
					str = "";
				}
				else
				{
					str2 = str;
					doCalculate(op,std::atof(str1.c_str()),std::atof(str2.c_str()));
					str1 = str;
					str = "";
					op = '-';
				}
			}
			
			break;
		}
		case ID_BUTTON_MULTI:
		{
			if(op == ' ')
			{
				str1 = str;
				op = '*';
				max = 0;
				str = "";
			}
			else
			{
				str2 = str;
				doCalculate(op,std::atof(str1.c_str()),std::atof(str2.c_str()));
				str1 = str;
				str = "";
				op = '*';
			}
			break;
		}
		case ID_BUTTON_DIVIDE:
		{
			if(op == ' ')
			{
				str1 = str;
				op = '/';
				max = 0;
				str = "";
			}
			else
			{
				str2 = str;
				if(str2 == "0")
				{
					SetWindowText(hwndResult,"ERROR");
					str = "";
					str1 = "";
					str2 = "";
					op = ' ';
				}
				else
				{
					doCalculate(op,std::atof(str1.c_str()),std::atof(str2.c_str()));
					str1 = str;
					str = "";
					op = '/';
				}
				
			}
			break;
		}
		case ID_BUTTON_SQRT:
		{
			str1 = str;
			if(std::atof(str1.c_str())<0)
			{
				SetWindowText(hwndResult,"ERROR");
			}
			else
			{
				resultNum = sqrt(std::atof(str1.c_str()));
				std::string tmp_stri  = std::to_string(static_cast<double long>(resultNum));
				SetWindowText(hwndResult,tmp_stri.c_str());
			}
			break;
		}	
		case ID_BUTTON_EQUAL:
			l:
			if(iFlag == 1)
			{	
				for(int i=0;i<(int)str.length();i++)
				{
					if(str.at(i)=='+' || str.at(i)=='-' || str.at(i)=='*' || str.at(i)=='/' || str.at(i)=='%')
					{
						op = str.at(i);
						str1 = str.substr(0,i);
						str = str.substr(i+1,str.length());
						iFlag = 0;
						break;
					}
				}
			}
			str2 = str;
			fNum1 = std::atof(str1.c_str());
			fNum2 = std::atof(str2.c_str());
			switch(op)
			{
			case '+':
				resultNum = fNum1 + fNum2;
				break;
			case '-':
				resultNum = fNum1 - fNum2;
				break;
			case '%':
				resultNum = (int)fNum1 % (int)fNum2;
				break;
			case '*':
				if(op == '*' && chujin == 1 && minus2 == fNum2)
				{
					resultNum = minus1;
					chujin = 0;
				}
				else
				{
					resultNum = fNum1 * fNum2;
				}
				break;
			case '/':
				if(fNum2 == 0.0)
				{
					SetWindowText(hwndResult,"ERROR");
				}
				else
				{
					resultNum = (double)fNum1 / (double)fNum2;
					static double tmp_result = resultNum * 100000000;
					static std::string tmp_stri = std::to_string(static_cast<double long>(tmp_result));
					if(tmp_stri.at(tmp_stri.length()-1) != '0')
					{
						minus1 = fNum1;
						minus2 = fNum2;
						chujin = 1;
					}
				}
				break;
			}
			//const char *t ;
			//t = str3.c_str();
			//_gcvt(resultNum,18,(char *)t);
			str3 = std::to_string(static_cast<double long>(resultNum));
			if(op != '/' || fNum2 != 0.0){
				SetWindowText(hwndResult,str3.c_str());
				//SetWindowText(hwndResult,t);
			}
			op = ' ';
			str = str3;
			break;
		}
		return 0;
	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd,&ps);
			SetTextColor(hdc,RGB(255,0,0));
			SetBkColor(hdc,GetSysColor(COLOR_3DFACE));
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_CHAR://WM_CHAR:
		{
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

void doCalculate(char oper, double fNum1, double fNum2)
{
	static double resultNum;
	switch(oper)
	{
	case '+':
		resultNum = fNum1 + fNum2;
		break;
	case '-':
		resultNum = fNum1 - fNum2;
		break;
	case '%':
		resultNum = (int)fNum1 % (int)fNum2;
		break;
	case '*':
		if(oper == '*' && chujin == 1 && minus2 == fNum2)
		{
			resultNum = minus1;
			chujin = 0;
		}
		else
		{
			resultNum = fNum1 * fNum2;
		}
		break;
	case '/':
		if(fNum2 == 0.0)
		{
			SetWindowText(hwndResult,"ERROR");
		}
		else
		{
			resultNum = (double)fNum1 / (double)fNum2;
			static double tmp_result = resultNum * 100000000;
			static std::string tmp_stri = std::to_string(static_cast<double long>(tmp_result));
			if(tmp_stri.at(tmp_stri.length()-1) != '0')
			{
				minus1 = fNum1;
				minus2 = fNum2;
				chujin = 1;
			}
		}
		break;
	}
	
	str3 = std::to_string(static_cast<double long>(resultNum));
	if(oper != '/' || fNum2 != 0.0){
		SetWindowText(hwndResult,str3.c_str());
	}
	str = str3;
	return;
}