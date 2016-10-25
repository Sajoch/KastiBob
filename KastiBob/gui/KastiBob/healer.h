#ifndef HEALER_H
#define HEALER_H

#include <QDialog>

namespace Ui {
class Healer;
}

class Healer : public QDialog
{
    Q_OBJECT

public:
    explicit Healer(QWidget *parent = 0);
    ~Healer();

private:
    Ui::Healer *ui;
};

#endif // HEALER_H
