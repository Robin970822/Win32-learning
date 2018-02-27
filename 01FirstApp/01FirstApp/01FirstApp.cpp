// 01FirstApp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	// 调用API函数MessageBox
	int nSelect = ::MessageBox(NULL, TEXT("Hello, Windows 10"), TEXT("Greetings"), MB_OKCANCEL);
	if (nSelect == IDOK)
		cout << "用户选择了“确定”按钮" << endl;
	else
		cout << "用户选择了“取消”按钮" << endl;

	return 0;
}

