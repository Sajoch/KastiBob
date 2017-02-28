#ifndef __RUNMAIN
#define __RUNMAIN

#include <QtCore/QObject>

class RunMain: public QObject{
	Q_OBJECT
	
  class LoginForm* lf;
  class CharSelect* cs;
  class GameWindow* gw;
  class DatLoader* datobjs;
	class SpriteLoader* sprobjs;
	class LoaderThread* lt;
	class ConfigFile* paths;
	class Client* tclient;
	bool stateLoadedResources;
	
public:
  RunMain();
	~RunMain();
  
  void delAllWindows();
	void loadedResources();
	void loadedResourcesBar(double a);
  void GoToLoginForm();
  void GoToCharSelect();
  void GoToGameWindow();
	class DatLoader* getDatobjs();
	class SpriteLoader* getSpr();
	class Client* getClient();
	class Client* getClient(class Client* v);
	void errorMsg(QString msg);
};

#endif