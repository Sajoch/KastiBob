#include <QtGui/QPainter>

class ImageDraw{
	int height;
	int width;
	int frameSize;
	size_t frameIndex;
	size_t animatedFrames;
	bool changed;
	bool idleAnimated;
	int pixelsX;
	int pixelsY;
	int blockWidth;
	int blockHeight;
	int blockSize;
	QRect imageArea;
	std::vector<QImage> imgs;
public:
	ImageDraw(class SpriteLoader* sprs, class DatObject* itemTemplate, int x, int y);
	bool needDraw();
	void draw(QPainter& p, QRect& area, double scale);
	void nextFrameAnimation();
	void colorize(QColor head, QColor body, QColor legs, QColor foot);
	void dumpImages(std::string bpath);
};