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
int*(*xtea_encrypt_ret)(int*, int*);
int*(*xtea_decrypt_ret)(int*, int*);

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
void showHex(char* buf, size_t len){
	const char abc[] = "0123456789ABCDEF";
	uint8_t c;
	for(size_t i=0;i<len;i++){
		c = buf[i];
		cout<<"0x"<<abc[(c>>4)&0x0f]<<abc[(c)&0x0f]<<" ";
		//cout<<(void*)(uint8_t)<<" ";
	}
	cout<<endl;
}


int __stdcall sendWrapper(int sock, char* buf, int size, int flag){
	int ret = WS_send(sock, buf, size, flag);
	cout<<"call "<<ret<<" = send("<<sock<<","<<size<<","<<flag<<");"<<endl;
	showBuffer(buf, size);
}

int* xtea_encryptWrapper(int* buf, int* keys){
	cout<<"wrte ";
	showHex((char*)buf, 8);
	return xtea_encrypt_ret(buf, keys);
}
int* xtea_decryptWrapper(int* buf, int* keys){
	int* ret = xtea_decrypt_ret(buf, keys);
	cout<<"read ";
	showHex((char*)ret, 8);
	return ret;
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
	
	//hook xtea_encrypt
	{
		xtea_encrypt_ret = (int*(*)(int*, int*))(baseAddress+0x14ff80);
		char* xtea_encrypt_func = (char*)(baseAddress+0x15021d);
		cout<<"xtea_encrypt "<<(void*)xtea_encrypt_func<<endl;
		unsigned char hook[] = {0xE8, 0x5E, 0xFD, 0xFF, 0xFF};
		hook[0] = 0xE8;
		uint32_t xtea_encrypt_add = (uint32_t)&xtea_encryptWrapper - (uint32_t)xtea_encrypt_func - 5;
		memcpy(&hook[1], (void*)&xtea_encrypt_add, 4);
		change_memory(&xtea_encrypt_func[0],(void*)hook,5);
	}
	//hook xtea_decrypt
	{
		xtea_decrypt_ret = (int*(*)(int*, int*))(baseAddress+0x1500b0);
		char* xtea_decrypt_func = (char*)(baseAddress+0x15023d);
		cout<<"xtea_decrypt "<<(void*)xtea_decrypt_func<<endl;
		unsigned char hook[] = {0xE8, 0x6E, 0xFF, 0xFF, 0xFF};
		hook[0] = 0xE8;
		uint32_t xtea_decrypt_add = (uint32_t)&xtea_decryptWrapper - (uint32_t)xtea_decrypt_func - 5;
		memcpy(&hook[1], (void*)&xtea_decrypt_add, 4);
		change_memory(&xtea_decrypt_func[0],(void*)hook,5);
	}
	//hook send
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
