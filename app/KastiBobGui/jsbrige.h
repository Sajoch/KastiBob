#ifndef JSBRIGE_H
#define JSBRIGE_H

#include <QtCore/QObject>

class JSBrige : public QObject
{

public:
    explicit JSBrige(QObject *parent = 0);
signals:

public slots:
  QString get();
};

#endif // JSBRIGE_H
