#include "hexas.h"

static HMODULE g_dllModule;

//int __cdecl sub_46B060(char*, char)
typedef int(__cdecl* CPrint)(char*, char);
CPrint cprint;


// unload dll
DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(g_dllModule, 0);
}

DWORD WINAPI ThreadFunc(LPVOID p)
{
	cprint = (CPrint)0x46B060;
	while (1)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			cprint((char*)"Console Hacked", ' ');
			Sleep(200);
		}
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			CreateThread(NULL, 0, EjectThread, 0, 0, 0);
		}
	}
}




BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_dllModule = hModule;
		CreateThread(NULL, 0, ThreadFunc, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}