#ifndef ALERTS_H
#define ALERTS_H

#include <QDialog>

namespace Ui {
class Alerts;
}

class Alerts : public QDialog
{
    Q_OBJECT

public:
    explicit Alerts(QWidget *parent = 0);
    ~Alerts();

private:
    Ui::Alerts *ui;
};

#endif // ALERTS_H
