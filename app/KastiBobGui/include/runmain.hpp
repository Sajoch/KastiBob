#ifndef __RUNMAIN
#define __RUNMAIN

class RunMain{
public:
	
	Q_OBJECT
	
  class QApplication* a;
  class LoginForm* lf;
  class CharSelect* cs;
  class GameWindow* gw;
  
  RunMain(int argc, char** argv);
  
  int ret();

  void delAllWindows();

  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
};

#endif