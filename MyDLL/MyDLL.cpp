// MyDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MyDLL.h"


// 这是导出变量的一个示例
MYDLL_API int nMyDLL=0;

// 这是导出函数的一个示例。
MYDLL_API int fnMyDLL(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 MyDLL.h
CMyDLL::CMyDLL()
{
    return;
}

int CMyDLL::sum(int a, int b)
{
	m = a;
	n = b;
	return m + n;
}
