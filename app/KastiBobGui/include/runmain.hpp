#ifndef __RUNMAIN
#define __RUNMAIN

#include <QtCore/QObject>

class RunMain: public QObject{
	Q_OBJECT
	
  class LoginForm* lf;
  class CharSelect* cs;
  class GameWindow* gw;
  
public:
  RunMain();
	~RunMain();
  
  void delAllWindows();

  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
};

#endif