#ifndef __RENDERAREA_HPP
#define __RENDERAREA_HPP

#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include <mutex>

class RenderArea: public QWidget{
	Q_OBJECT
	
public:
	RenderArea(class GameWindow *parent, class RunMain* app);
	~RenderArea();
	
protected:
	void paintEvent(QPaintEvent *event) override;
signals:
	void THupdate();
private:
	//std::vector<> sprites;
	void oneSquare(QPainter* p, class Square& sq, int x, int y);
	bool clearImage(int x, int y);
	bool addImageOn(int x, int y, class QImage& n);
	void onChangeClient(class GameWindow *parent);
	std::mutex mapStateChange;
	size_t allNode;
	class Client* c;
	std::map<uint32_t, QImage> maps;
	bool showPanel;
	class RunMain* runapp;
	class QPainter* painter;
};

#endif