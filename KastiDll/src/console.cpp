#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>

void openconsole() {
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  int consoleHandleR, consoleHandleW ;
  long stdioHandle;
  FILE *fptr;

  if (AllocConsole()) {
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
}
