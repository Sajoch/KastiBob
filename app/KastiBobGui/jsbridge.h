#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QtCore/QObject>

class JSBridge : public QObject
{
  Q_OBJECT
public:
  explicit JSBridge(QObject *parent = 0);
  void setGW(class GameWindow* that);

  Q_INVOKABLE void logout();
  Q_INVOKABLE void charSelect();
  Q_INVOKABLE QString getImg(size_t id);
  Q_INVOKABLE void move(int dir);
  Q_INVOKABLE void look(uint32_t id);
  Q_INVOKABLE uint32_t getX();
  Q_INVOKABLE uint32_t getY();
  Q_INVOKABLE void callAfterUpdate();
private:
  class GameWindow* gamewindow;
};

#endif // JSBRIDGE_H
