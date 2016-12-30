#include "jsbrige.h"

JSBrige::JSBrige(QObject *parent) : QObject(parent)
{

}

QString JSBrige::get(){
    return "test123";
}
