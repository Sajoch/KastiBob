#include "renderarea.hpp"

#include <QtGui/QPainter>
#include <QtGui/QColor>
#include "runmain.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include "square.hpp"
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

void RenderArea::oneSquare(QPainter* p, Square& sq, int x, int y){
	sq.dump();
	for(int32_t z = 8; z>6; z--){
		uint32_t items = sq.getItemsAmount(z);
		if(items>0){
			//cout<<"draw Z "<<z<<" items "<<items<<endl;
		}
		for(uint32_t i=0;i<items;i++){
			Item& it = sq.getItem(z, i);
			DatObject* td = it.getTemplate();
			if(td == 0){
				continue;
			}
			if(td->images.size() == 1){
				cout<<"draw id "<<it.getId()<<" = "<<x<<","<<y<<endl;
				std::string img = runapp->getSpr()->getRaw(td->images[0]);
				QImage n((uchar*)img.c_str(), 32, 32, 4*32, QImage::Format_RGBA8888);
				//std::string path = "tmp/q"+std::to_string(x)+"x"+std::to_string(y)+"x"+std::to_string(z)+".png";
				//n.save(path.c_str(),"PNG");
				//mapStateChange.lock();
				p->drawImage(x*32, y*32, n);
				//addImageOn(x, y, n);
				//mapStateChange.unlock();
			}else if(td->images.size()>1){
				for(size_t imgs=0;imgs<td->images.size();imgs++){
					size_t sprId = td->images[imgs];
					if(sprId == 0) continue;
					std::string img = runapp->getSpr()->getRaw(sprId);
					QImage n((uchar*)img.c_str(), 32, 32, 4*32, QImage::Format_RGBA8888);
					//std::string path = "tmp/q"+std::to_string(it.getId())+"i"+std::to_string(sprId)+".png";
					//n.save(path.c_str(),"PNG");
					p->drawImage(x*32, y*32, n);
					break;
				}
				//mapStateChange.lock();
			}
		}
	}
}

void RenderArea::onChangeClient(GameWindow *parent){
	/*int32_t sx, sy, mx, my;
	mx = 12;
	my = 12;
	sx = c->getX() - 6;
	sy = c->getY() - 6;
	for(int32_t x=0;x<mx;x++){
		for(int32_t y=0;y<my;y++){
			mapStateChange.lock();
			clearImage(x, y);
			mapStateChange.unlock();
			Square& sq = c->getSquare(sx+x, sy+y);
			oneSquare(sq, x, y);
		}
	}
	*/
	update();
}

bool RenderArea::clearImage(int x, int y){
	maps[x*12+y] = QPixmap(32, 32).toImage();
	return true;
}

bool RenderArea::addImageOn(int x, int y, QImage& n){
	QPainter p(&maps[x*c->getMapViewY()+y]);
	p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	p.drawImage(0, 0, n);
	return true;
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
		//QString text = "Dupak";
		//painter->drawText(12, 21, 80, 60, Qt::AlignLeft|Qt::AlignTop, text);
	}
	int32_t sx, sy, mx, my;
	mx = 12;
	my = 12;
	sx = c->getX() - 6;
	sy = c->getY() - 6;
	for(int32_t x=0;x<mx;x++){
		for(int32_t y=0;y<my;y++){
			mapStateChange.lock();
			clearImage(x, y);
			mapStateChange.unlock();
			Square& sq = c->getSquare(sx+x, sy+y);
			oneSquare(painter, sq, x, y);
		}
	}
	/*
	int id = 0;
	int32_t mx = 12;
	int32_t my = 12;
	mapStateChange.lock();
	for(int32_t x=0;x<mx;x++){
		for(int32_t y=0;y<my;y++){
			//cout<<"width "<<maps[id].width()<<endl;
			painter->drawImage(x*32, y*32, maps[id]);
			id++;
		}
	}
	mapStateChange.unlock();
	*/
	delete painter;
}