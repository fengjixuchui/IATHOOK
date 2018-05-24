// IATHOOK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



DWORD g_dwIATHookFlag = 0;	//HOOK 状态 1 HOOK 0 未HOOK
DWORD g_dwOldAddr;			//原始函数地址
DWORD g_dwNewAddr;			//HOOK函数地址

DWORD pOldFuncAddr = (DWORD)GetProcAddress(LoadLibrary(L"user32.dll"), "MessageBoxA");

int WINAPI MyMessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
BOOL SetIATHook(DWORD dwOldAddr, DWORD dwNewAddr);


int main()
{
	SetIATHook(1,2);

	getchar();
	return 0;
}

int WINAPI MyMessageBox(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	//定义函数指针
	typedef int (WINAPI *PFNMESSAGEBOX)(HWND, LPCSTR, LPCSTR, UINT);

	//获取参数
	printf("%x %s %s %x", hWnd, lpText, lpCaption, uType);

	//执行真正的函数
	int ret = ((PFNMESSAGEBOX)pOldFuncAddr)(hWnd, lpText, lpCaption, uType);

	//获取返回值
	printf("return:%x\n", ret);

	return ret;
}

BOOL SetIATHook(DWORD dwOldAddr, DWORD dwNewAddr)
{
	BOOL dFlag = false;
	DWORD dwImageBase = 0;
	PDWORD pFuncAddr = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor = NULL;

	//get imageBase
	dwImageBase = (DWORD)GetDriverModuleHandle(NULL);
	//pNtHeader = (PIMAGE_NT_HEADERS)(dwImageBase + ((PIMAGE_DOS_HEADER)dwImageBase)->e_lfanew);
	//pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwImageBase + pNtHeader->OptionalHeader.DataDirectory->VirtualAddress);
	int sd = 0;
	

	return TRUE;
}
