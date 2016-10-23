#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <TlHelp32.h>
#include "objectfile.hpp"
using namespace std;

extern unsigned long remoteCode_length;
extern unsigned const char* remoteCode_data;

bool getModules(std::vector<MODULEENTRY32>& modules, int pid){
	//std::vector<MODULEENTRY32> modules;
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	me32.dwSize = sizeof( MODULEENTRY32 );
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32, pid );
	if( hModuleSnap == INVALID_HANDLE_VALUE ) {
		return false;
	}
	if( !Module32First( hModuleSnap, &me32 ) ) {
		CloseHandle( hModuleSnap );     // Must clean up the snapshot object!
		return false;
	}
	do {
	  modules.push_back(me32);
	} while( Module32Next( hModuleSnap, &me32 ) );
	return true;
	//CloseHandle( hModuleSnap );
	/*
	for (std::vector<MODULEENTRY32>::iterator it = modules.begin(); it != modules.end(); ++it) {
		if ( it->szModule == "Kernel32.dll" ) {

		}
	}*/
}

bool inject(int pid){
	//TODO inject
	HANDLE hProc=OpenProcess(
		PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,
		FALSE,
		pid
	);
	if(!hProc){
		cout<<"OpenProcess "<<pid<<" failed"<<endl;
		return false;
	}
	ObjectFile injecter(remoteCode_data, remoteCode_length);
	//cout<<GetProcAddress(hProc, "MessageBoxA")<<endl;

	void* proc_injected_memory = VirtualAllocEx(hProc, 0, injecter.size(), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if(!proc_injected_memory){
		cout<<"VirtualAllocEx "<<pid<<" failed"<<endl;
		return false;
	}

	std::vector<MODULEENTRY32> modules;
	getModules(modules, pid);
	HMODULE hKernel32 = 0;
	void* baseKernel32 = 0;
	for (std::vector<MODULEENTRY32>::iterator it = modules.begin(); it != modules.end(); ++it) {
		if (strcmp(it->szModule, "KERNEL32.DLL")==0) {
			hKernel32 = it->hModule;
			baseKernel32 = it->modBaseAddr;
			break;
		}
	}
	//injecter.setAddress("_addr_GetProcAddress",0xDEADBEEB);
	//injecter.setAddress("_addr_LoadLibrary",gpa);
	//injecter.setAddress("_addr_GetModuleHandle",0xDEADBEEF);
	injecter.setAddress("_addr_baseKernel32",(size_t)baseKernel32);
	injecter.remap(proc_injected_memory);
	void* RemoteThreadFunc=injecter.getAddress("_RemoteThread");

	if(!WriteProcessMemory(hProc, proc_injected_memory, injecter.map(), injecter.size(), 0)){
		cout<<"WriteProcessMemory "<<pid<<" failed"<<endl;
		return false;
	}
	cout<<"base "<<proc_injected_memory<<endl;
	cout<<"ep "<<RemoteThreadFunc<<endl;
	cin.get();
	HANDLE hRThread=CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)RemoteThreadFunc, 0, 0, 0);
	if(!hRThread){
		cout<<"CreateRemoteThread "<<pid<<" failed"<<endl;
		return false;
	}
	CloseHandle(hRThread);
	//*/
	CloseHandle(hProc);
	return true;
}

int main(int argc, char* argv[]){
	if(argc<2){
		cout<<"using: <exeName>"<<endl;
		return 1;
	}
	string exeName = argv[1];
	cout<<"Finding processes by name "<<exeName<<endl;
	map<int,string> processes;
	PROCESSENTRY32 e;
	e.dwSize=sizeof(PROCESSENTRY32);
	HANDLE th32s = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(th32s == INVALID_HANDLE_VALUE){
		cout<<"Toolhelp32Snapshot INVALID_HANDLE_VALUE"<<endl;
		return 2;
	}
	if(Process32First(th32s,&e) == FALSE){
		cout<<"Process32First ERROR_NO_MORE_FILES"<<endl;
		return 3;
	}
	while(Process32Next(th32s, &e) == TRUE){
		processes[e.th32ProcessID]=e.szExeFile;
	}
	CloseHandle(th32s);

	for(map<int,string>::iterator it=processes.begin();it!=processes.end();){
		if(it->second!=exeName)
			it = processes.erase(it);
		else
			++it;
	}
	cout<<"Found "<<processes.size()<<" correct process"<<endl;
	for(map<int,string>::iterator it=processes.begin();it!=processes.end();++it){
		cout<<"Injecting to PID "<<it->first<<" - ";
		cout<<flush;
		if(inject(it->first)){
			cout<<"done"<<endl;
		}else{
			cout<<"exiting"<<endl;
			return 4;
		}
	}
	if(processes.size())
		cout<<"Everything done"<<endl;
	return 0;
}
