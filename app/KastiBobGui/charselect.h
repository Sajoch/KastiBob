#ifndef _CHARSELECT_H
#define _CHARSELECT_H

#include "uis_cpp/charselect.gen.h"
#include <QtWidgets/QDialog>



class CharSelect : public QDialog
{

public:
    explicit CharSelect(QWidget *parent = 0);
    ~CharSelect();
private:
  Ui_CharSelect* ui;
};

#endif // CHARSELECT_H
