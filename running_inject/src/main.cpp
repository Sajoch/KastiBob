#include <iostream>
#include <windows.h>
#include <string>
#include <map>
#include <TlHelp32.h>
using namespace std;

bool inject(int pid){
	//TODO inject
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
			cout<<"fail"<<endl;
			cout<<"exiting"<<endl;
			return 4;
		}
	}
	cout<<"Everything done"<<endl;
	return 0;
}
