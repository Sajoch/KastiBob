#ifndef __RUNMAIN
#define __RUNMAIN

#include <QtCore/QObject>

class RunMain: public QObject{
	Q_OBJECT
	
  class LoginForm* lf;
  class CharSelect* cs;
  class GameWindow* gw;
  class DatLoader* datobjs;
	class LoaderThread* lt;
	bool stateLoadedResources;
	
public:
  RunMain();
	~RunMain();
  
  void delAllWindows();
	void loadedResources();
  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
	class DatLoader* getDatobjs();
};

#endif