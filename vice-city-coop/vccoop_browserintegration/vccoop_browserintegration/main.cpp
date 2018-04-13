#include "stdafx.h"

#include <iostream>
#include <windows.h>

HKEY key;

bool DoesKeyExist()
{
	if (RegOpenKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\"), &key) != ERROR_SUCCESS)	
		return false;

	return true;
}

int main()
{
	setlocale(LC_ALL, "en_GB");

	if (DoesKeyExist()) {
		printf("Registry key already exists! Exiting.\n");
		return -1;
	}

	if (RegCreateKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\"), &key) != ERROR_SUCCESS)	{
		printf("Registry key could not be created! Exiting.\n");
		return -1;
	}
	else
	{
		if (RegCreateKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\DefaultIcon"), &key) != ERROR_SUCCESS) {
			printf("Registry key could not be created! Exiting.\n");
			return -1;
		}
		if (RegCreateKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\shell"), &key) != ERROR_SUCCESS) {
			printf("Registry key could not be created! Exiting.\n");
			return -1;
		}
		if (RegCreateKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\shell\\open"), &key) != ERROR_SUCCESS) {
			printf("Registry key could not be created! Exiting.\n");
			return -1;
		}
		if (RegCreateKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\shell\\open\\command"), &key) != ERROR_SUCCESS) {
			printf("Registry key could not be created! Exiting.\n");
			return -1;
		}
	}

	printf("Vice City CO-OP Browser Integration\nWritten by LemonHaze\n======================================\n");
	printf("[INFO] Registry keys created.\n");
	
	// Obtain GTA VC directory..
	char* buffer = new char[256];
	printf("Please enter GTAVC directory: ");
	std::cin >> buffer;
	
	// Create bat file..
	//start /D D:\GTAVC\ D:\GTAVC\gta-vc.exe "%*"
	char* fbuffer = new char[256];
	sprintf(fbuffer, "%s\\launcher.bat", buffer);
	FILE* f = fopen(fbuffer, "wb");
	sprintf(fbuffer, "start /D %s\\ %s\\gta-vc.exe \"%%*\"\n", buffer, buffer);
	fputs(fbuffer, f);
	fclose(f);
	delete[] fbuffer;

	sprintf(buffer, "%s\\launcher.bat %%1", buffer);

	// Set directory...
	if (RegOpenKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop\\shell\\open\\command"), &key) != ERROR_SUCCESS)
		return false;

	const WCHAR *pwcsName;
	int nChars = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);
	pwcsName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, buffer, -1, (LPWSTR)pwcsName, nChars);
	const wchar_t* s = pwcsName;
	if (RegSetValueEx(key, TEXT(""), 0, REG_SZ, reinterpret_cast<BYTE const*>(s), sizeof(wchar_t)*(wcslen(s) + 1)) != ERROR_SUCCESS)	{
		RegCloseKey(key);
		printf("Unable to set registry value value_name\n");
	} else	{
		printf("Registry value set.\n");
	}

	// Set URL Handler
	if (RegOpenKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop"), &key) != ERROR_SUCCESS)
		return false;

	sprintf(buffer, "VCCOOP URL Handler");
	nChars = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);
	pwcsName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, buffer, -1, (LPWSTR)pwcsName, nChars);
	s = pwcsName;
	if (RegSetValueEx(key, TEXT(""), 0, REG_SZ, reinterpret_cast<BYTE const*>(s), sizeof(wchar_t)*(wcslen(s) + 1)) != ERROR_SUCCESS) {
		RegCloseKey(key);
		printf("Unable to set registry value.\n");
	} else {
		printf("Registry value set.\n");
	}

	// Set URL Protocol
	if (RegOpenKeyW(HKEY_CLASSES_ROOT, TEXT("vccoop"), &key) != ERROR_SUCCESS)
		return false;

	sprintf(buffer, "");
	nChars = MultiByteToWideChar(CP_ACP, 0, buffer, -1, NULL, 0);
	pwcsName = new WCHAR[nChars];
	MultiByteToWideChar(CP_ACP, 0, buffer, -1, (LPWSTR)pwcsName, nChars);
	s = pwcsName;
	if (RegSetValueEx(key, TEXT("URL Protocol"), 0, REG_SZ, reinterpret_cast<BYTE const*>(s), sizeof(wchar_t)*(wcslen(s) + 1)) != ERROR_SUCCESS) {
		RegCloseKey(key);
		printf("Unable to set registry value.\n");
	}
	else {
		printf("Registry value set.\n");
	}
	RegCloseKey(key);

	printf("\n\nAll values set.\n");

	delete[] buffer;
	delete[] pwcsName;

	system("PAUSE");
    return 0;
}