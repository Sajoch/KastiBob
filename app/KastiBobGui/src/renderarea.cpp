#include "renderarea.hpp"
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtCore/QObject>
#include "runmain.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include "square.hpp"
#include "gamewindow.h"
#include "render_image.hpp"
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
	c->afterRecv([&](){
		onChangeClient(parent);
	});
	QObject::connect(&animationChanger, &QTimer::timeout, [&](){
		std::vector<ImageDraw>::iterator it;
		mapStateChange.lock();
		for(it=map_draws.begin();it!=map_draws.end();++it){
			ImageDraw& r = *it;
			r.nextFrameAnimation();
		}
		mapStateChange.unlock();
		update();
	});
	animationChanger.start(100);
	//connect(this, &RenderArea::update, this, [&](){
		//cout<<"rysuj"<<endl;
    //parent->update();
  //});
}
RenderArea::~RenderArea(){
	c->clearCallbacks();
}

void RenderArea::oneSquare(Square& sq, int x, int y, int z){
	uint32_t len;
	len = sq.getItemsAmount(z);
	Item it;
	Creature cr;
	for(uint32_t i=0;i<len;i++){
		if(sq.getItem(z, i, it)){
			DatObject* td = it.getTemplate();
			if(td != 0){
				mapStateChange.lock();
				map_draws.push_back(ImageDraw(runapp->getSpr(), td, x, y));
				mapStateChange.unlock();
			}
		}
	}
	len = sq.getCreatureAmount(z);
	for(uint32_t i=0;i<len;i++){
		if(sq.getCreature(z, i, cr)){
			DatObject* td = cr.getTemplate();
			if(td != 0){
				ImageDraw idraw(runapp->getSpr(), td, x, y);
				if(td->getId() == 136){
					idraw.colorize(QColor(0,0,0), QColor(0,0,0), QColor(0,0,0), QColor(0,0,0));
				}
				mapStateChange.lock();
				//idraw.dumpImages("tmp/iod"+std::to_string(td->getId())+"x");
				map_draws.push_back(idraw);
				mapStateChange.unlock();
			}
		}
	}
}

void RenderArea::onChangeClient(GameWindow *parent){
	if(c->editedMap){
		cout<<"editedMap"<<endl;
		c->editedMap = false;
		int32_t sx, sy, mx, my, x, y;
		mx = 17;
		my = 13;
		sx = c->getX() - 8;
		sy = c->getY() - 6;
		std::vector<std::pair<std::pair<int32_t, int32_t>, Square>> sqs;
		for(x=0;x<mx;x++){
			for(y=0;y<my;y++){
				Square& sq = c->getSquare(sx+x, sy+y);
				std::pair<int32_t, int32_t> cordy(x, y);
				sqs.push_back(std::pair<std::pair<int32_t, int32_t>, Square>(cordy, sq));
			}
		}
		mapStateChange.lock();
		map_draws.clear();
		mapStateChange.unlock();
		std::vector<std::pair<std::pair<int32_t, int32_t>, Square>>::iterator it;
		int32_t bz = 7;
		int32_t ez = 0;
		if(currenctFloor){
			bz = 7;
			ez = 6;
		}
		for(int32_t z = bz; z>ez; z--){
			for(it=sqs.begin();it!=sqs.end();++it){
				x = (*it).first.first;
				y = (*it).first.second;
				Square& sq = (*it).second;
				oneSquare(sq, x, y, z);
			}
		}
	}
	update();
}
void RenderArea::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	size_t w, h, mapWidth, panelWidth;
	w = painter.device()->width();
	h = painter.device()->height();
	mapWidth = h;
	if(showPanel){
		panelWidth = w - mapWidth;
		QRect rect(w-panelWidth, 0, panelWidth, h);
		painter.fillRect(rect, QColor(0, 5, 0, 255));
		//QString text = "Dupak";
		//painter.drawText(12, 21, 80, 60, Qt::AlignLeft|Qt::AlignTop, text);
	}
	QRect mapArea(0, 0, 200, 200);
	std::vector<ImageDraw>::iterator it;
	mapStateChange.lock();
	for(it=map_draws.begin();it!=map_draws.end();++it){
		ImageDraw& r = *it;
		r.draw(painter, mapArea, 1.5);
	}
	mapStateChange.unlock();
	painter.end();
}