#include "kastibob.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KastiBob w;
    w.show();

    return a.exec();
}
