#include <iostream>
#include "runmain.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	RunMain app(argc, argv);
	app.show_login();
	return app.exec();
}
