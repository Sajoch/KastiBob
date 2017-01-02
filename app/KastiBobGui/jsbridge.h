#ifndef JSBRIDGE_H
#define JSBRIDGE_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QJsonDocument>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>

class JSBridge : public QObject
{
  Q_OBJECT
public:
  explicit JSBridge(QObject *parent = 0);
  void setGW(class GameWindow* that, QWebView* _webview);
  void CrossCallAfterUpdate();

  Q_INVOKABLE void logout();
  Q_INVOKABLE void charSelect();
  Q_INVOKABLE QString getImg(size_t id);
  Q_INVOKABLE void move(int dir);
  Q_INVOKABLE void look(uint32_t id);
  Q_INVOKABLE void callAfterUpdate(QVariant data);
private:
  class GameWindow* gamewindow;
  QWebFrame* mframe;
};

#endif // JSBRIDGE_H
