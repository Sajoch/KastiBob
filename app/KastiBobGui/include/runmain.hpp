#ifndef __RUNMAIN
#define __RUNMAIN

#include <QtCore/QObject>

class RunMain: public QObject{
	Q_OBJECT
	
  class LoginForm* lf;
  class CharSelect* cs;
  class GameWindow* gw;
<<<<<<< HEAD
  class DatLoader* datobjs;
	class SpriteLoader* sprobjs;
	class LoaderThread* lt;
	class ConfigFile* paths;
	class Client* tclient;
	bool stateLoadedResources;
	
=======
  
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
public:
  RunMain();
	~RunMain();
  
  void delAllWindows();
<<<<<<< HEAD
	void loadedResources();
  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
	class DatLoader* getDatobjs();
	class SpriteLoader* getSpr();
	class Client* getClient();
	class Client* getClient(class Client* v);
	void errorMsg(QString msg);
=======

  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
};

#endif