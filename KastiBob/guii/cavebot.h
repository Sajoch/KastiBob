#ifndef CAVEBOT_H
#define CAVEBOT_H

#include <QDialog>

namespace Ui {
class Cavebot;
}

class Cavebot : public QDialog
{
    Q_OBJECT

public:
    explicit Cavebot(QWidget *parent = 0);
    ~Cavebot();

private:
    Ui::Cavebot *ui;
};

#endif // CAVEBOT_H
