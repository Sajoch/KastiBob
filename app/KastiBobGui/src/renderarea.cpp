#include "renderarea.hpp"
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtCore/QObject>
#include "runmain.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include "square.hpp"
#include "outfit.hpp"
#include "gamewindow.h"
#include "render_image.hpp"
#include "client.hpp"
#include "item.hpp"
#include <iostream>

using namespace std;

/*
jeżeli to bedzie nie wydajne to zawsze mozna mape zrenderowac do bitmapy a potem
co niej dorysowywac/usuwac, przesuwac, renderowac animacje i itd.
*/

RenderArea::RenderArea(GameWindow *parent, RunMain* app):
	QWidget(parent),
	runapp(app)
{
	setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
	viewX = viewY = 0;
	showPanel = true;
	currenctFloor = true;
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
				ImageDraw idraw(runapp->getSpr(), td, x, y);
				idraw.blend();
				mapStateChange.lock();
				map_draws.push_back(idraw);
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
				if(td->getBlend() > 0){
					Outfit& skin = cr.getApperance();
					idraw.colorize(skin.getHeadColor(), skin.getBodyColor(), 
												 skin.getLegsColor(), skin.getFeetColor());
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
		viewX = 12;
		viewY = 10;
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
		int32_t bz = c->getZ();
		int32_t ez = 0;
		if(c->under){
			ez = bz - 1;
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
	/*
	double sqSizeX, sqSizeY, sqSize;
	sqSizeX = mapWidth / (double) viewX;
	sqSizeY = mapWidth / (double) viewY;
	if(sqSizeX < sqSizeY){
		sqSize = sqSizeX;
	}else{
		sqSize = sqSizeY;
	}
	double scale = sqSize / 32;
	cout<<"scale = "<<scale<<endl;
	*/
	QRect mapArea(0, 0, mapWidth, mapWidth);
	painter.fillRect(mapArea, QColor(0, 0, 0, 255));
	std::vector<ImageDraw>::iterator it;
	mapStateChange.lock();
	for(it=map_draws.begin();it!=map_draws.end();++it){
		ImageDraw& r = *it;
		r.draw(painter, mapArea, 1);
	}
	mapStateChange.unlock();
	painter.end();
}