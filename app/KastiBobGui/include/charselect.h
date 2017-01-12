#ifndef _CHARSELECT_H
#define _CHARSELECT_H

#include "charselect.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>

class CharSelect : public QDialog{
public:
    explicit CharSelect(QWidget *parent = 0);
    ~CharSelect();
    void enter();
    void logout();
    void load();
    void keyPressEvent(QKeyEvent *e);
private:
  Ui_CharSelect* ui;
};

#endif // CHARSELECT_H
