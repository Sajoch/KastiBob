#include "renderarea.hpp"

#include <QtGui/QPainter>
#include <QtGui/QColor>
#include "runmain.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include "client.hpp"
#include <iostream>

using namespace std;

RenderArea::RenderArea(RunMain* parent):
	QWidget(0),
	runapp(parent)
{
	setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
	showPanel = true;
	c = runapp->getClient();
	maps.resize(c->getMapViewX()*c->getMapViewY());
	map_objs.resize(c->getMapViewX()*c->getMapViewY());
	c->afterRecv([&](){
		onChangeClient();
	});
}
RenderArea::~RenderArea(){
	c->clearCallbacks();
}

void RenderArea::onChangeClient(){
	c->getDrawMap(map_objs);
	size_t m = map_objs.size(); //TODO always same
	DatObject* td;
	for(size_t i=0;i<m;i++){
		td = map_objs[i];
		if(td->images.size() == 1){
			setImageOn(i, runapp->getSpr()->getImage(td->images[0]));
		}else{
			cout<<"error ground to much sprites"<<endl;
		}
	}
}

bool RenderArea::setImageOn(size_t id, std::string buf){
	if(maps[id].loadFromData((unsigned char*)buf.c_str(), buf.size(), "PNG")){
		return true;
	}else{
		return false;
	}
}

bool RenderArea::setImageOn(int x, int y, std::string buf){
	if(maps[x*c->getMapViewY()+y].loadFromData((unsigned char*)buf.c_str(), buf.size(), "PNG")){
		return true;
	}else{
		return false;
	}
}

void RenderArea::paintEvent(QPaintEvent *event){
	painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);
	size_t w, h, mapWidth, panelWidth;
	w = painter->device()->width();
	h = painter->device()->height();
	mapWidth = h;
	if(showPanel){
		panelWidth = w - mapWidth;
		QRect rect(w-panelWidth, 0, panelWidth, h);
		painter->fillRect(rect, QColor(0, 255, 0, 255));
		QString text = "Dupak";
		painter->drawText(12, 21, 80, 60, Qt::AlignLeft|Qt::AlignTop, text);
	}
	int id = 0;
	int mx = c->getMapViewX();
	int my = c->getMapViewY();
	for(int x=0;x<mx;x++){
		for(int y=0;y<my;y++){
			painter->drawImage(x*32, y*32, maps[id]);
			id++;
		}
	}
	delete painter;
}