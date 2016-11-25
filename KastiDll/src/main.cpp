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

int(*WS_send)(int, char*, int, int);


void showBuffer(char* buf, int size){
	string buffer(buf, size);
	if(buffer.size()>6){
		uint16_t len = ((buffer[1]&0xff)<<8) | (buffer[0]&0xff);
		if((buffer.size()-2) >= len){
			buffer = buffer.substr(6);
			//encrypted buffer
		}
	}
}


int __stdcall sendWrapper(int sock, char* buf, int size, int flag){
	int ret = WS_send(sock, buf, size, flag);
	cout<<"call "<<ret<<" = send("<<sock<<","<<size<<","<<flag<<");"<<endl;
	showBuffer(buf, size);
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
	
	//TODO find xtea keys
	
	HMODULE ws2 = GetModuleHandle("ws2_32.dll");
	WS_send = (int(*)(int, char*, int, int))GetProcAddress(ws2, "send");
	if(WS_send != 0){
		char* fromPingSend = (char*)(baseAddress+0x177F3F);
		unsigned char hook[] = {0xFF, 0x15, 0x08, 0x26, 0x5B, 0x00};
		hook[0] = 0xE8;
		uint32_t sendWrapper_add = (uint32_t)&sendWrapper - (uint32_t)fromPingSend - 5;
		memcpy(&hook[1], (void*)&sendWrapper_add, 4);
		hook[5] = 0x90;
		cout<<"wrapper "<<(void*)&sendWrapper<<endl;
		cout<<"rva "<<(void*)sendWrapper_add<<endl;
		change_memory(&fromPingSend[0],(void*)hook,6);
	}
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
	//string m_n = "1";
	//change_memory(&rsa_n_num[0], (void*)m_n.data(), m_n.size());
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
