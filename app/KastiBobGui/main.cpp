#include "loginform.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLibrary>
#include <QtCore/QTimer>
#include "src/client.hpp"

Client* tclient;
QTimer *logic_loop;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm* tmp = new LoginForm();
    tmp->show();
    return a.exec();
}
