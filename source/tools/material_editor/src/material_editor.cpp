#include <ballistic.base.h>

#ifdef BALLISTIC_API_WIN32

#include <windows.h>

// DLL entry function (called on load, unload, ...)
BOOL APIENTRY DllMain (HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	return TRUE;
}

#endif