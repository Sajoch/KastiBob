#include <string>
#include "config.hpp"
#include <QtWidgets/QApplication>

class RunMain: public QApplication{
	Config paths;
	class Ui_LoginForm* ui_login;
public:
	RunMain(int argc, char** argv);
	// windows
	void show_login();
	void show_charSelect();
	void show_game();

	// client s methods
	void client_logout();

};
