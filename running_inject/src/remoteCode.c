#include <windows.h>


int load(){
	return 1;
}

static void* addr_MessageBox = (void*)0xDEADBEAF;

unsigned int RemoteThread(void* arg){
	int(*_MessageBox)(HWND, LPCTSTR, LPCTSTR, UINT) = (int(*)(HWND, LPCTSTR, LPCTSTR, UINT)) addr_MessageBox;//addr_MessageBox;
	_MessageBox(0,"Halo","Hello World!", MB_OK);
	return 0;

}

int main(){
	return 0;
}
