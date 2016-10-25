#include <windows.h>

#ifdef BUILDING_DLL
	#define DLL __declspec(dllexport)
#else
	#define DLL __declspec(dllimport)
#endif

extern "C" BOOLEAN DLL DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved){
	MessageBoxA(0,"asd","ads",MB_OK);
  return TRUE;
 }
