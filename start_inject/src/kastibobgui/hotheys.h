#ifndef HOTHEYS_H
#define HOTHEYS_H

#include <QDialog>

namespace Ui {
class Hotheys;
}

class Hotheys : public QDialog
{
    Q_OBJECT

public:
    explicit Hotheys(QWidget *parent = 0);
    ~Hotheys();

private:
    Ui::Hotheys *ui;
};

#endif // HOTHEYS_H
