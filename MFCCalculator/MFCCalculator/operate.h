#pragma once
#include "stdafx.h"

// 处理数字
void Number(CStatic*, CStatic*, wstring, wstring, bool&);

// 处理符号
void Operator(CStatic*, CStatic*, wstring, bool&);

// 计算结果
void Equal(CStatic*, CStatic*, wstring, bool&);

// 处理小数点
// 判断主屏幕中是否有小数点
void Dot(CStatic*, CStatic*, bool&);

// 处理根号
void Sqrt(CStatic*, CStatic*, bool&);

// 清空
void Clear(CStatic*, CStatic*, bool&);