#include <windows.h>


int load(){
	return 1;
}

//static void* addr_MessageBox = (void*)0xDEADBEAF;
void* addr_GetProcAddress = 0;
void* addr_LoadLibrary = 0;
void* addr_GetModuleHandle = 0;

unsigned int RemoteThread(void* arg){
	FARPROC(*_GetProcAddress)(HMODULE,LPCSTR) = addr_GetProcAddress;
	HMODULE(*_LoadLibrary)(LPCTSTR) = addr_LoadLibrary;
	HMODULE(*_GetModuleHandle)(LPCTSTR) = addr_GetModuleHandle;
	int(*_MessageBox)(HWND, LPCTSTR, LPCTSTR, UINT);
	//int(*_MessageBox)(HWND, LPCTSTR, LPCTSTR, UINT) = (int(*)(HWND, LPCTSTR, LPCTSTR, UINT)) addr_MessageBox;//addr_MessageBox;
	//MessageBox(0,"Halo","Hello World!", MB_OK);
	HMODULE hDllUser32 = _LoadLibrary("User32.dll");
	_MessageBox=(void*)_GetProcAddress(hDllUser32,"MessageBoxA");
	_MessageBox(0,"Halo","Hello World!", MB_OK);
	return 0;

}
