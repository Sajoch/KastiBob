#include <windows.h>
#include <string>
#include <iostream>
#include "console.hpp"

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


int ep_main() {
	unsigned int baseAddress = (unsigned int)GetModuleHandle(0);
	openconsole();
	cout<<"Welcome in KastiBob_re"<<endl;
	//2421C8 -start
	string ret = "KastiBob_re module\nTibia Windows Client\n\nhttps://github.com/Sajoch/\nKastiBob2";
	//ret += to_string((unsigned int)baseAddress);
	//MessageBoxA(0, ret.c_str(), "Hello World!", MB_OK);
	char* tibia_info = (char*)(baseAddress+0x2421C8);
	char* rsa_n_num = (char*)(baseAddress+0x1B2610);
	//0x1571a2 - move big int - propable rsa
	//edit rsa n number
	//e is 65537
	//p - 269
	//q - 271
	//n - 72899
	//φ(n) - 268*270 = 72360
	//d - (d*n)%φ(n)=1
	//d - (d*65537)%72360=1
	//d - 13193
	string m_n = "1";
	change_memory(&rsa_n_num[0], (void*)m_n.data(), m_n.size());
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
