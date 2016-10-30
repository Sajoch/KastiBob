#include <windows.h>

#ifdef BUILDING_DLL
	#define DLL __declspec(dllexport)
#else
	#define DLL __declspec(dllimport)
#endif

extern "C" int DLL init(){
	int test=123;
	MessageBoxA(0,"Hello World!","Hello World!",MB_OK);
  return 1;
}
