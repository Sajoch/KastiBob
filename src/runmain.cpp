#include <iostream>
#include "runmain.hpp"

#include "ui_login.hpp"

using namespace std;

RunMain::RunMain(){
	paths = Config("configs/test.txt");
	paths.load();
	paths["NLOGIN"].setInt(123);
	paths["dislabled"].setString("dupa");
	
	paths.save();
}

void RunMain::show_login(){
	
}
void RunMain::show_charSelect(){
	
}
void RunMain::show_game(){
	
}