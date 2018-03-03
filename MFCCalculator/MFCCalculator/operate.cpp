#include "stdafx.h"
#include "operate.h"
#include <cmath>
#include <mmsystem.h>

void ShowMainScreen(CStatic*);
void ShowSubScreen(CStatic*);


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
wstring pre_opt;				// 输完数字时，记录上一次按下的有效运算
double dNum_tmp;				// 第一次按等号时，记录等号之前输入的数字
int cntEqual = 0;				// 记录连续等号次数

void Number(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring num, wstring opt, bool &isEqual)
{
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);
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
	screen_hwnd_main->GetWindowText(tmp, 256);
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
		screen_hwnd_main->SetWindowText(tmp);
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
			screen_hwnd_main->SetWindowText(tmp);
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

void Operator(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring opt, bool &isEqual)
{
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);
	// 连续等号次数清零
	cntEqual = 0;
	// 获取主屏幕上的内容
	screen_hwnd_main->GetWindowText(tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> mainText;
	buffer.clear();
	// 去除不必要的数字末尾小数点
	if (mainText[mainText.length() - 1] == '.')
	{
		mainText.erase(mainText.end() - 1);
		//MessageBox(NULL, mainText.c_str(), TEXT("去小数点"), MB_OK);
	}
	//MessageBox(NULL, tmp, TEXT("主屏幕中间值"), MB_OK);
	// 在之前进行等号计算结果，后输入运算符号，将结果作为被操作数，开始新一轮的计算
	if (isEqual == true)
	{
		double dtmp = 0.0;
		buffer << tmp;
		buffer >> dtmp;
		buffer.clear();
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		ShowMainScreen(screen_hwnd_main);
		dNum1 = dtmp;
	}

	// 如果第一次有效按下运算符，将当前主屏幕数字作为被操作数
	if (cnt == 0)
	{
		//MessageBox(NULL, NULL, tmp, MB_OK);
		buffer << tmp;
		buffer >> dNum1;
		buffer.clear();
	}

	// isNum为false，则前一个为运算符，直接替换当前辅屏幕中最后一位运算符
	if (isNum == false)
	{
		record[record.length() - 1] = opt[0];
		ShowSubScreen(screen_hwnd_sub);
	}
	// isNum为true,则进行以下操作
	// Step 1 将上一次有效运算符记录下来
	// Step 2 record += (mainText + op[0])
	// Step 3 在输入有效运算符的次数超过1时，计算前一步的结果
	// Step 4 将相关结果分别放进辅屏幕
	else
	{
		//pre_opt = opt;
		//MessageBox(NULL, pre_opt.c_str(), NULL, MB_OK);

		// 处理根号
		if (isSqrt == false)
		{
			record += mainText;
		}
		record += opt[0];

		ShowSubScreen(screen_hwnd_sub);
		if (cnt > 0)
		{
			Equal(screen_hwnd_main, screen_hwnd_sub, pre_opt, isEqual);
		}
		cnt++;
	}

	isNum = false;
	isDot = false;
	isSqrt = false;
}

void Equal(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, wstring opt, bool &isEqual)
{
	// 将焦点重新定位到主窗口上
	//SetFocus(hwnd);
	// 连续等号次数清零
	cntEqual = 0;
	// 获取主屏幕上的内容
	screen_hwnd_main->GetWindowText(tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> dNum2;
	buffer.clear();
	
	//MessageBox(NULL, tmp, tmp, MB_OK);

	if (cntEqual == 0)
	{
		dNum_tmp = dNum2;
	}

	if (isEqual == true)
	{
		dNum2 = dNum_tmp;
	}

	// 进行计算
	double epsilon = 1e-8;
	switch (opt[0])
	{
	case '+':
		dNum1 += dNum2;
		break;
	case '-':
		dNum1 -= dNum2;
		break;
	case '*':
		dNum1 *= dNum2;
		break;
	case '/':
		if (fabs(dNum2 - 0.0) < epsilon)
		{
			MessageBox(NULL, _T("除数不能为0！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
			return;
		}
		dNum1 /= dNum2;
		break;
	case '%':
	{
		if (fabs(dNum2 - 0.0) < epsilon)
		{
			MessageBox(NULL, _T("无法对零做模运算！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
			return;
		}
		int nNum1, nNum2;
		bool isInt_1 = false;
		bool isInt_2 = false;

		// 处理精度，当一个小数足够接近一个整数时，视其为整数进行运算
		if (dNum1 > epsilon && fabs(dNum1 - (int)(dNum1 + 0.5)) < epsilon)
		{
			isInt_1 = true;
			nNum1 = (int)(dNum1 + 0.5);
		}
		if (dNum2 > epsilon && fabs(dNum2 - (int)(dNum2 + 0.5)) < epsilon)
		{
			isInt_2 = true;
			nNum2 = (int)(dNum2 + 0.5);
		}
		if (dNum1 < -1.0 * epsilon && fabs(dNum1 - (int)(dNum1 - 0.5)) < epsilon)
		{
			isInt_1 = true;
			nNum1 = (int)(dNum1 - 0.5);
		}
		if (dNum2 < -1.0 * epsilon && fabs(dNum1 - (int)(dNum1 - 0.5)) < epsilon)
		{
			isInt_2 = true;
			nNum2 = (int)(dNum2 - 0.5);
		}
		if (isInt_1 == true && isInt_2 == true)
		{
			nNum1 %= nNum2;
			dNum1 = nNum1;
		}
		else
		{
			MessageBox(NULL, _T("无法对0或小数做模运算！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
			return;
		}
	}
		break;
	default:
		break;
	}

	// 显示结果
	// 辅屏幕
	if (dNum1 > 1e+308 || dNum1 < -1.0 * 1e+308)
	{
		MessageBox(NULL, _T("无法进行计算！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		return;
	}

	buffer << tmp;
	buffer >> mainText;
	buffer.clear();

	// 多次连续按等号的辅屏幕
	if (isEqual == true && cntEqual > 0)
	{
		if (cnt == 0)
		{
			return;
		}
		record.clear();
		record += (mainText + pre_opt);
		buffer << dNum_tmp;
		buffer >> mainText;
		buffer.clear();
		record += (mainText + _T("="));
		ShowSubScreen(screen_hwnd_sub);
	}

	// 第一次按等于号时的辅屏幕
	if (isEqual == true && cntEqual == 0)
	{
		if (mainText[mainText.length() - 1] == '.')
		{
			mainText.erase(mainText.end() - 1);
		}
		if (isSqrt == false)
		{
			record += mainText;
		}
		record += _T("=");
		cntEqual++;
	}
	ShowSubScreen(screen_hwnd_sub);

	// 主屏幕
	if (cnt == 0)
	{
		ShowMainScreen(screen_hwnd_main);
		return;
	}
	buffer << setprecision(9) << dNum1;
	buffer >> mainText;
	buffer.clear();
	ShowMainScreen(screen_hwnd_main);
}

void Dot(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool &isEqual)
{
	// 将焦点置于主窗口
	//SetFocus(hwnd);

	if (isDot == true)
	{
		return;
	}
	else
	{
		wstringstream buffer;

		// 若刚才按下等号后按小数点
		if (isEqual == true)
		{
			Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		}
		// 获取主屏幕上的内容
		screen_hwnd_main->GetWindowText(tmp, 256);
		buffer << tmp;
		buffer >> mainText;
		buffer.clear();
		// 若输入新的运算符或刚才为未确定的根号计算则清空并置为0
		if (isNum == false || isSqrt == true)
		{
			if (isSqrt == true)
			{
				record = record_tmp;
				ShowSubScreen(screen_hwnd_sub);
			}
			mainText = _T("0");
		}
		if (mainText.length() < 11)
		{
			mainText += _T(".");
		}
		ShowMainScreen(screen_hwnd_main);
	}
	isDot = true;
	isNum = true;
	isSqrt = false;
}

void Sqrt(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool &isEqual)
{
	//SetFocus(hwnd);

	if (isSqrt == false)
	{
		record_tmp = record;
	}

	screen_hwnd_main->GetWindowText(tmp, 256);
	wstringstream buffer;
	buffer << tmp;
	buffer >> dNum2;
	buffer.clear();

	if (dNum2 >= 0.0)
	{
		dNum2 = sqrt(dNum2);
		buffer << dNum2;
		buffer >> mainText;
		buffer.clear();

		if (isSqrt == true)
		{
			record = record_tmp;
		}
		record += _T("√(");
		record += tmp;
		record += _T(")");
	}
	else
	{
		MessageBox(NULL, _T("无效输入！"), _T("警告！"), MB_OK | MB_ICONEXCLAMATION);
		mainText = _T("0");
		Clear(screen_hwnd_main, screen_hwnd_sub, isEqual);
		return;
	}

	ShowMainScreen(screen_hwnd_main);
	ShowSubScreen(screen_hwnd_sub);

	isSqrt = true;
	isNum = true;
}

void Clear(CStatic* screen_hwnd_main, CStatic* screen_hwnd_sub, bool &isEqual)
{
	isNum = true;
	isDot = false;
	isSqrt = false;
	isEqual = false;
	dNum1 = dNum2 = dNum_tmp = 0.0;
	cnt = cntEqual = 0;
	operators.clear();
	record.clear();
	pre_opt.clear();
	screen_hwnd_main->SetWindowText(_T("0"));
	screen_hwnd_sub->SetWindowText( _T(""));
}

void ShowSubScreen(CStatic* screen_hwnd_sub)
{
	wstringstream buffer;
	buffer << record;
	buffer >> tmp;
	buffer.clear();
	screen_hwnd_sub->SetWindowText(tmp);
}

void ShowMainScreen(CStatic* screen_hwnd_main)
{
	wstringstream buffer;
	buffer << mainText;
	buffer >> tmp;
	buffer.clear();
	screen_hwnd_main->SetWindowText(tmp);
}
