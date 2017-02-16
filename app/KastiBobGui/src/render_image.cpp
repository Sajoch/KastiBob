#include "render_image.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"
#include <iostream>

using namespace std;

ImageDraw::ImageDraw(SpriteLoader* sprs, DatObject* tmp, int x, int y){
	int blockWidth = tmp->width;
	int blockHeight = tmp->height;
	idleAnimated = tmp->idleAnimated;
	blendFrames = tmp->getBlend();
	pixelsX = x * 32;
	pixelsY = y * 32;
	frameIndex = 0;
	width = blockWidth * 32;
	height = blockHeight * 32;
	changed = true;
	imageArea = QRect(x-width, y-height, width, height);
	animatedFrames = tmp->animatedFrames;
	int frameBlockSize = blockWidth * blockHeight;
	int frameAmount = tmp->images.size() / frameBlockSize;
	for(int frame_id=0;frame_id<frameAmount;frame_id++){
		QImage frame(width, height, QImage::Format_ARGB32);
		frame.fill(QColor(0,0,0,0));
		QPainter p_frame(&frame);
		for(int fx=0;fx<blockWidth;fx++){
			for(int fy=0;fy<blockHeight;fy++){
				int idx = (frame_id * frameBlockSize) + frameBlockSize - 1 - (fy*blockWidth+fx);
				size_t sprId = tmp->images[idx];;
				if(sprId != 0){
					std::string* img = sprs->get(sprId).getRawPointer();
					QImage n((uchar*)img->c_str(), 32, 32, 4*32, QImage::Format_RGBA8888);
					p_frame.drawImage(fx*32, fy*32, n);
				}
			}
		}
		p_frame.end();
		imgs.push_back(frame);
	}
}
void ImageDraw::nextFrameAnimation(){
	if(idleAnimated){
		frameIndex++;
		if(frameIndex >= animatedFrames){
			frameIndex = 0;
		}
		changed = true;
	}
}
void ImageDraw::blend(){
	size_t l = imgs.size();
	for(size_t i=1;i<l;i+=blendFrames){
		QImage& orig = imgs[i-1];
		QPainter o_paint(&orig);
		for(int bi=1;bi<blendFrames;bi++){
			QImage& mask = imgs[i];
			o_paint.drawImage(0, 0, mask);
			imgs.erase(imgs.begin()+i);
			i--;
			l--;
		}
	}
}
void ImageDraw::draw(QPainter& p, QRect& area, double scale){
	QImage& frame = imgs[frameIndex];
	int ox = (pixelsX-width+32)*scale;
	int oy = (pixelsY-height+32)*scale;
	p.drawImage(ox, oy, frame.scaled(width*scale, height*scale));
}
bool ImageDraw::needDraw(){
	return true; //TODO
}
void ImageDraw::colorize(QColor head, QColor body, QColor legs, QColor feet){
	cout<<"colorize"<<endl;
	size_t l = imgs.size();
	for(size_t i=1;i<l;i+=2){
		QImage& orig = imgs[i-1];
		QPainter o_paint(&orig);
		QImage& mask = imgs[i];
		int red=0;
		int green=0;
		int w=mask.width();
		int h=mask.height();
		int bytesPerColor = mask.bytesPerLine()/w;
		for(int y=0;y<h;y++){
			QRgb* line = (QRgb*)mask.scanLine(y);
			for(int x=0;x<w;x++){
				QRgb* c = line + x;
				int r, g, b;
				r = qRed(*c);
				g = qGreen(*c);
				b = qBlue(*c);
				if(r==255 && g==255){
					QColor n = head;
					*c = n.rgb();
				}else if(r==255){
					QColor n = body;
					*c = n.rgb();
				}else if(g==255){
					QColor n = legs;
					*c = n.rgb();
				}else if(b==255){
					QColor n = feet;
					*c = n.rgb();
				}
			}			
		}
		o_paint.drawImage(0, 0, mask);
		imgs.erase(imgs.begin()+i);
		i--;
		l--;
	}
}
void ImageDraw::dumpImages(std::string bpath){
	for(size_t i=0;i<imgs.size();i++){
		std::string rpath = bpath+std::to_string(i)+".png";
		imgs[i].save(rpath.c_str(), "PNG");
	}
}