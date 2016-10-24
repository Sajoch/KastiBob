#include <windows.h>




//static void* addr_MessageBox = (void*)0xDEADBEAF;
unsigned int addr_baseKernel32 = 0;
unsigned int addr_GetProcAddress = 0;
unsigned int addr_LoadLibrary = 0;
unsigned int addr_GetModuleHandle = 0;

int Mstrcmp(char* a, char* b){
	while(*a!=0 || *b!=0){
		if(*a!=*b){
			return 0;
		}
		a++;
		b++;
	}
	return 1;
}

int loadFunction(){
	if(addr_baseKernel32 == 0){
		return 1;
	}
	IMAGE_DOS_HEADER* dos_header = (void*)addr_baseKernel32;
	IMAGE_NT_HEADERS* nt_headers = (void*)(addr_baseKernel32 + dos_header->e_lfanew);
	if (nt_headers->OptionalHeader.NumberOfRvaAndSizes < 1){
		return 2;
	}
	IMAGE_EXPORT_DIRECTORY* ed = (void*)(addr_baseKernel32 + nt_headers->OptionalHeader.DataDirectory[0].VirtualAddress);

	unsigned int names_ed = ed->AddressOfNames + addr_baseKernel32;
	unsigned int addresses_ed = ed->AddressOfFunctions + addr_baseKernel32;
	unsigned int ordinal_ed = ed->AddressOfNameOrdinals + addr_baseKernel32;
	for (unsigned int i=0;i<ed->NumberOfFunctions;i++){
		unsigned short* ordinal_rva = (unsigned short*)(ordinal_ed+i*2);
		unsigned int* func = (unsigned int*)(addresses_ed+(*ordinal_rva)*4);
		unsigned int* name_rva = (unsigned int*)(names_ed+i*4);
		char* name = (char*)(addr_baseKernel32+*name_rva);
		if (Mstrcmp(name, "GetProcAddress")){
			addr_GetProcAddress = addr_baseKernel32 + *func;
		}else if (Mstrcmp(name, "LoadLibraryA")){
			addr_LoadLibrary = addr_baseKernel32 + *func;
		}else if (Mstrcmp(name, "GetModuleHandle")){
			addr_GetModuleHandle = addr_baseKernel32 + *func;
		}
	}
	return 0;
}

unsigned int RemoteThread(void* arg){
	loadFunction();
	FARPROC(*_GetProcAddress)(HMODULE,LPCSTR) = (void*)addr_GetProcAddress;
	HMODULE(*_LoadLibrary)(LPCTSTR) = (void*)addr_LoadLibrary;
	HMODULE(*_GetModuleHandle)(LPCTSTR) = (void*)addr_GetModuleHandle;
	int(*_MessageBox)(HWND, LPCTSTR, LPCTSTR, UINT);
	//HMODULE hDllUser32 = _LoadLibrary("User32.dll");
	//_MessageBox=(void*)_GetProcAddress(hDllUser32,"MessageBoxA");
	_LoadLibrary("Kasti_re.dll");
	return 0;
}
