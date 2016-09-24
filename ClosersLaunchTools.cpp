// ClosersLaunchTools.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

void ClosersGameLaunch(int service)
{

	if (service > 3 || service <= 0)
		return;

	WCHAR szPath[MAX_PATH * 2] = { 0 };
	WCHAR *szCommandline = (WCHAR*)malloc(MAX_PATH * 2);


	if (szCommandline == NULL )
		return;

	memset(szCommandline, '0', MAX_PATH * 2);

	lstrcpyW(szCommandline, L" _L http ://cdnupdatecls.tiancity.cn/ _LN ");

	GetCurrentDirectoryW(MAX_PATH*2, szPath);

	lstrcatW(szPath, L"\\CW.exe");

	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	/*
	电一
	008FDEA8   _L http://cdnupdatecls.tiancity.cn/ _LN 1
	电二
	008FDEA8   _L http://cdnupdatecls.tiancity.cn/ _LN 2
	网一
	008FDEA8   _L http://cdnupdatecls.tiancity.cn/ _LN 11
	*/

	switch (service)
	{
	case 1:
		lstrcatW(szCommandline, L"1");
		break;
	case 2:
		lstrcatW(szCommandline, L"2");
		break;
	case 3:
		lstrcatW(szCommandline, L"11");
		break;
	default:
		lstrcatW(szCommandline, L"1");
		break;
	}

	si.cb = 0x44;
	memset(&si.lpReserved,0,0x40);

	if (!CreateProcess(szPath, szCommandline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		if (!ShellExecuteW(NULL, L"runas", szPath, szCommandline, 0, 5))
		{
			printf("Launch faild!\n");
			free(szCommandline);
			return;
		}
	}
	
	free(szCommandline);
}


int main(int arc, char** arv)
{

	int service = 2;
	SetConsoleTitleA("ClosersLaunchTools");

	if (arc < 2)
	{
		printf("No Invalid Parameter\n");
		printf("1.电信一区 2.电信二区......\n");
		return 0;
	}

	service = atoi(arv[1]);

	ClosersGameLaunch(service);

    return 0;
}

