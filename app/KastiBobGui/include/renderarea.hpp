#ifndef __RENDERAREA_HPP
#define __RENDERAREA_HPP

#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
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
	int viewX;
	int viewY;
	QTimer animationChanger;
	std::map<uint32_t, class ImageDraw> creature_draw;
	std::vector<class ImageDraw> map_draws;
	void oneSquare(class Square& sq, int x, int y, int z);
	void onChangeClient(class GameWindow *parent);
	std::mutex mapStateChange;
	bool currenctFloor;
	class Client* c;
	bool showPanel;
	class RunMain* runapp;
};

#endif