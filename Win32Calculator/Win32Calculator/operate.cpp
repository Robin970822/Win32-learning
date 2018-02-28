#include "stdafx.h"
#include "operate.h"

void ShowMainScreen(HWND);
void ShowSubScreen(HWND);


// 状态转移标志
bool isNum = true;				// false表示之前按下运算符状态，true表示之前按下数字状态
bool isDot = false;				// false表示之前非小数状态，true表示之前小数状态
bool isSqrt = false;			// false表示之前未按下根号状态，true表示之前按下根号状态

double dNum1 = 0.0;				// 被操作数
double dNum2 = 0.0;				// 操作数
wstring operators;				// 记录符号
WCHAR tmp[256];					// 记录主屏幕上的值（中间值）
wstring mainText;				// 记录主屏幕上的值
wstring record;					// 记录算式
wstring record_tmp;				// 记录有效根号计算前的算式
int cnt = 0;					// 计算有效运算符个数
wstring pre_opt;					// 输完数字时，记录上一次按下的有效运算
double dNum_tmp;					// 第一次按等号时，记录等号之前输入的数字
int cntEqual = 0;				// 记录连续等号次数

void Number(HWND hwnd, HWND screen_hwnd_main, HWND screen_hwnd_sub, wstring num, wstring opt, bool &isEqual)
{
	// 将焦点重新定位到主窗口上
	SetFocus(hwnd);
	// 连续等号次数清零
	cntEqual = 0;
	// 记录前次有效运算符
	pre_opt = opt;
	// 等号计算后直接输入数字，先清除
	if (isEqual == true)
	{
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
	}
	// 获取主屏幕上的内容
	GetWindowText(screen_hwnd_main, tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> mainText;
	buffer.clear();

	// isNum是false，前一个是运算符，直接替换当前屏幕中的数字
	if (isNum == false)	
	{
		wstringstream buffer;
		buffer << num;
		buffer >> tmp;
		buffer.clear();
		SetWindowText(screen_hwnd_main, tmp);
	}
	else
	{
		// 判断前导0，如是，直接替换当前屏幕中的数字
		if (mainText.length() == 1 && mainText[0] == '0')
		{
			wstringstream buffer;
			buffer << num;
			buffer >> tmp;
			buffer.clear();
			SetWindowText(screen_hwnd_main, tmp);
		}
		else if (mainText.length() < 11)
		{
			if (isSqrt == false)
			{
				mainText += num[0];
			}
			else
			{
				record = record_tmp;
				mainText = num[0];
				ShowSubScreen(screen_hwnd_sub);
			}
			ShowMainScreen(screen_hwnd_main);
		}
	}

	isNum = true;
	isSqrt = false;
}

void Operator(HWND hwnd, HWND screen_hwnd_main, HWND screen_hwnd_sub, wstring opt, bool &isEqual)
{
}

void Equal(HWND, HWND, HWND, wstring, bool &)
{
}

void hasDot(HWND, HWND, HWND, bool &)
{
}

void Sqrt(HWND, HWND, HWND, bool &)
{
}

void Clear(HWND, HWND, bool &)
{
}
