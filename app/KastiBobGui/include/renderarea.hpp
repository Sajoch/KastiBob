#ifndef __RENDERAREA_HPP
#define __RENDERAREA_HPP

#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QPixmap>
#include <QtWidgets/QWidget>

class RenderArea: public QWidget{
	Q_OBJECT
	
public:
	RenderArea(class RunMain* parent);
	~RenderArea();
	bool setImageOn(int x, int y, std::string buf);
	
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	bool setImageOn(size_t id, std::string buf);
	void onChangeClient();
	class Client* c;
	std::vector<class DatObject*> map_objs;
	std::vector<QImage> maps;
	bool showPanel;
	class RunMain* runapp;
	class QPainter* painter;
};

#endif