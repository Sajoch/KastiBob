#include "loginform.h"
#include "charselect.h"
#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginForm w;
    //CharSelect w;
    GameWindow w;
    w.show();

    return a.exec();
}
