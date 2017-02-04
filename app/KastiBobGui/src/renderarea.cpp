#include "renderarea.hpp"

#include <QtGui/QPainter>
#include <QtGui/QColor>
#include "runmain.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include "gamewindow.h"
#include "client.hpp"
#include "item.hpp"
#include <iostream>

using namespace std;

RenderArea::RenderArea(GameWindow *parent, RunMain* app):
	QWidget(parent),
	runapp(app)
{
	setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
	showPanel = true;
	c = runapp->getClient();
	allNode = c->getMapViewX()*c->getMapViewY();
	c->afterRecv([&](){
		onChangeClient(parent);
	});
	//connect(this, &RenderArea::update, this, [&](){
		//cout<<"rysuj"<<endl;
    //parent->update();
  //});
}
RenderArea::~RenderArea(){
	c->clearCallbacks();
}

void RenderArea::onChangeClient(GameWindow *parent){
	Item ground;
	uint32_t sx, sy, id, mx, my;
	DatObject* td;
	mx = c->getMapViewX();
	my = c->getMapViewY();
	sx = c->getX() - mx;
	sy = c->getY() - my;
	mx *= 2;
	my *= 2;
	for(uint32_t x=0;x<mx;x++){
		for(uint32_t y=0;y<my;y++){
			c->getGroundSquare(ground, sx+x, sy+y);
			id = ground.getId();
			td = runapp->getDatobjs()->getItem(id);
			if(td == 0){
				continue;
			}
			if(td->images.size() >= 1){
				cout<<"draw id "<<id<<" "<<x<<","<<y<<endl;
				std::string img = runapp->getSpr()->getImage(td->images[0]);
				mapStateChange.lock();
				setImageOn(x, y, img);
				mapStateChange.unlock();
			}else{
				cout<<"ground id "<<id<<endl;
				cout<<"error ground to much sprites "<<td->images.size()<<endl;
				return;
			}
		}
	}
	update();
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
	int mx = 2 * c->getMapViewX();
	int my = 2 * c->getMapViewY();
	mapStateChange.lock();
	for(int x=0;x<mx;x++){
		for(int y=0;y<my;y++){
			//cout<<"width "<<maps[id].width()<<endl;
			painter->drawImage(x*32, y*32, maps[id]);
			id++;
		}
	}
	mapStateChange.unlock();
	delete painter;
}