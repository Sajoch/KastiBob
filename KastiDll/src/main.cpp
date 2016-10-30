#include <windows.h>
#include <string>

using namespace std;

#ifdef BUILDING_DLL
	#define DLL __declspec(dllexport)
#else
	#define DLL __declspec(dllimport)
#endif

int ep_main() {
	HMODULE baseAddress = GetModuleHandle(0);
	string ret = "Text: ";
	ret += to_string((unsigned int)baseAddress);
	MessageBoxA(0, ret.c_str(), "Hello World!", MB_OK);
}


extern "C" int DLL init(){
  return ep_main();
}
