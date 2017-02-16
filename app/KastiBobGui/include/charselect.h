#ifndef _CHARSELECT_H
#define _CHARSELECT_H

#include "charselect.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>
#include "config.hpp"

class CharSelect : public QDialog{
  Q_OBJECT
  
public:
    explicit CharSelect(class RunMain* app);
    ~CharSelect();
    void enter();
    void logout();
    void load();
    void keyPressEvent(QKeyEvent *e);
signals:
  void logouted();
  void entered();
<<<<<<< HEAD
  void errorMsg(QString msg, QString type);
=======
>>>>>>> abd77b599c1b4eee9908b15350175c3b260553fa
private:
  class RunMain* runapp;
  ConfigFile loginConf;
  size_t rChar;
  int rAutoChar;
  Ui_CharSelect* ui;
};

#endif // CHARSELECT_H
