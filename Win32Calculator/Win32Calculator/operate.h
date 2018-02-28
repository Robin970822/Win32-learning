#pragma once
#include "stdafx.h"

// 处理数字
void Number(HWND, HWND, HWND, wstring, wstring, bool&);

// 处理符号
void Operator(HWND, HWND, HWND, wstring, bool&);

// 计算结果
void Equal(HWND, HWND, HWND, wstring, bool&);

// 处理小数点
// 判断主屏幕中是否有小数点
void Dot(HWND, HWND, HWND, bool&);

// 处理根号
void Sqrt(HWND, HWND, HWND, bool&);

// 清空
void Clear(HWND, HWND, bool&);