#include <string>
#include "config.hpp"

class RunMain{
	Config paths;
	
public:
	RunMain();
	// windows
	void show_login();
	void show_charSelect();
	void show_game();
	
	// client s methods
	void client_logout();
	
};