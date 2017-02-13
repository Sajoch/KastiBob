#include "render_image.hpp"
#include "datLoader.hpp"
#include "sprLoader.hpp"

ImageDraw::ImageDraw(SpriteLoader* sprs, DatObject* itemTemplate, int x, int y){
	int blockWidth = itemTemplate->width;
	int blockHeight = itemTemplate->height;
	pixelsX = x * 32;
	pixelsY = y * 32;
	frameIndex = 0;
	width = blockWidth * 32;
	height = blockHeight * 32;
	changed = true;
	imageArea = QRect(x-width, y-height, width, height);
	animatedFrames = itemTemplate->animatedFrames;
	int frameBlockSize = blockWidth * blockHeight;
	int frameAmount = itemTemplate->images.size() / frameBlockSize;
	for(int frame_id=0;frame_id<frameAmount;frame_id++){
		QImage frame(width, height, QImage::Format_RGBA8888_Premultiplied);
		frame.fill(QColor(0,0,0,0));
		QPainter p_frame(&frame);
		for(int fx=0;fx<blockWidth;fx++){
			for(int fy=0;fy<blockHeight;fy++){
				int idx = (frame_id * frameBlockSize) + frameBlockSize - 1 - (fy*blockWidth+fx);
				size_t sprId = itemTemplate->images[idx];;
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
	if(animatedFrames>1){
		frameIndex++;
		if(frameIndex >= animatedFrames){
			frameIndex = 0;
		}
		changed = true;
	}
}
void ImageDraw::draw(QPainter& p, QRect& area){
	QImage& frame = imgs[frameIndex];
	int ox = pixelsX-width+32;
	int oy = pixelsY-height+32;
	p.drawImage(ox, oy, frame);
}
bool ImageDraw::needDraw(){
	return true; //TODO
}