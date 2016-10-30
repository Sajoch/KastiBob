#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <iostream>

using namespace std;

#ifdef BUILDING_DLL
	#define DLL __declspec(dllexport)
#else
	#define DLL __declspec(dllimport)
#endif

bool change_memory(void* dest, void* src, size_t size){
	DWORD oldP;
	VirtualProtect(dest, size, PAGE_EXECUTE_WRITECOPY, &oldP);
	memcpy(dest, src, size);
	VirtualProtect(dest, size, oldP, &oldP);
	return true;
}
void openconsole() {
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  int consoleHandleR, consoleHandleW ;
  long stdioHandle;
  FILE *fptr;

  AllocConsole();
  std::string strW = "KastiBob_re Console";
  SetConsoleTitle( strW.c_str() );

  EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE , MF_GRAYED);
  DrawMenuBar(GetConsoleWindow());

  GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo );

  stdioHandle = (long)GetStdHandle( STD_INPUT_HANDLE );
  consoleHandleR = _open_osfhandle( stdioHandle, _O_TEXT );
  fptr = _fdopen( consoleHandleR, "r" );
  *stdin = *fptr;
  setvbuf( stdin, NULL, _IONBF, 0 );

  stdioHandle = (long) GetStdHandle( STD_OUTPUT_HANDLE );
  consoleHandleW = _open_osfhandle( stdioHandle, _O_TEXT );
  fptr = _fdopen( consoleHandleW, "w" );
  *stdout = *fptr;
  setvbuf( stdout, NULL, _IONBF, 0 );

  stdioHandle = (long)GetStdHandle( STD_ERROR_HANDLE );
  *stderr = *fptr;
  setvbuf( stderr, NULL, _IONBF, 0 );

	freopen_s(&fptr, "CONOUT$", "w", stdout);
	freopen_s(&fptr, "CONIN$", "r", stdin);
}

int ep_main() {
	unsigned int baseAddress = (unsigned int)GetModuleHandle(0);
	//openconsole();
	//cout<<"Welcome in KastiBob_re"<<endl;
	//2421C8 -start
	string ret = "KastiBob_re module\n\nTibia Windows Client\n\nhttps://github.com/Sajoch/KastiBob";
	//ret += to_string((unsigned int)baseAddress);
	//MessageBoxA(0, ret.c_str(), "Hello World!", MB_OK);
	char* tibia_info = (char*)(baseAddress+0x2421C8);
	char* rsa_public_key = (char*)(baseAddress+0x1B2610);
	//0x1571a2 - move big int - propable rsa
	//edit rsa public key
	change_memory(&rsa_public_key[0], (void*)"1", 2);
	//Tibia
	//Kasti
	memcpy(&tibia_info[0], &ret[0], ret.size());
	tibia_info[ret.size()]=0;
	//change_memory(&tibia_info[0],(void*)"Kasti",5);

	//void(*myTest)() = (void(*)())(baseAddress + 0xc2e70);
	//myTest();

	//MessageBoxA(0, "ok", "Hello World!", MB_OK);
	return 0;
}


extern "C" int DLL init(){
  return ep_main();
}
