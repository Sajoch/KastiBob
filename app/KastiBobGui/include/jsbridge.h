#ifndef __JSBRIDGE_H
#define __JSBRIDGE_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QJsonDocument>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>

class JSBridge : public QObject
{
  Q_OBJECT
public:
  explicit JSBridge(class RunMain* app);
  ~JSBridge();
  void setGW(class GameWindow* that, QWebView* _webview);
  void CrossCallAfterUpdate();
  void sendDataToJS(QString json);

  Q_INVOKABLE void logout();
  Q_INVOKABLE void charSelect();
  Q_INVOKABLE void start();
  Q_INVOKABLE QString getImg(int id);
  Q_INVOKABLE void move(int dir);
  Q_INVOKABLE void look(int id);
  Q_INVOKABLE void callAfterUpdate(QVariant data);
private:
  class GameWindow* gamewindow;
  QWebView* webView;
  QWebFrame* mframe;
signals:
  void sendData(QString json);
  void errorMsg(QString msg, QString type);
};

#endif // JSBRIDGE_H
