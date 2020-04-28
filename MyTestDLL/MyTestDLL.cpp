// MyTestDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MyTestDLL.h"


// 这是导出变量的一个示例
MYTESTDLL_API int nMyTestDLL=0;

// 这是导出函数的一个示例。
MYTESTDLL_API int fnMyTestDLL(void)
{
    return 42;
}
MYTESTDLL_API CMyTestDLL * GetMyDll(int a)
{
	return new CMyTestDLL(a);
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 MyTestDLL.h
CMyTestDLL::CMyTestDLL(int m,int n)
{
	this->a = m;
	this->b = n;
}

CMyTestDLL::CMyTestDLL(int m)
{
	this->a = m;
}

int CMyTestDLL::sum()
{
	return a+b;
}
