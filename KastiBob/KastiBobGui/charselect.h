#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <QDialog>

namespace Ui {
class CharSelect;
}

class CharSelect : public QDialog
{
    Q_OBJECT

public:
    explicit CharSelect(QWidget *parent = 0);
    ~CharSelect();

private:
    Ui::CharSelect *ui;
};

#endif // CHARSELECT_H
