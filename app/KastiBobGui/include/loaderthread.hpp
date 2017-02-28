#ifndef __LOADERTHREAD_HPP
#define __LOADERTHREAD_HPP


#include <QtCore/QThread>

class LoaderThread: public QThread{
	Q_OBJECT
public:
	LoaderThread(class DatLoader* _dat, class SpriteLoader* _spr);
signals:
	void img(double a);
private:
	class DatLoader* dat;
	class SpriteLoader* spr;
	void run();
};

#endif