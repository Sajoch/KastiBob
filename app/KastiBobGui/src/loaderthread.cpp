#include "loaderthread.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"

LoaderThread::LoaderThread(DatLoader* _dat, SpriteLoader* _spr){
	dat = _dat;
	spr = _spr;
}

void LoaderThread::run(){
	dat->load();
	spr->load();
	spr->loadAll([&](double a){
		img(a);
	});
}