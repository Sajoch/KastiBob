#ifndef _CHARSELECT_H
#define _CHARSELECT_H

#include "uis_cpp/charselect.gen.h"
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>

class CharSelect : public QDialog{
public:
    explicit CharSelect(QWidget *parent = 0);
    ~CharSelect();
    void enter();
    void logout();
    void keyPressEvent(QKeyEvent *e);
private:
  Ui_CharSelect* ui;
};

#endif // CHARSELECT_H
