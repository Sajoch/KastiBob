#ifndef KASTIBOB_H
#define KASTIBOB_H

#include <QMainWindow>

namespace Ui {
class KastiBob;
}

class KastiBob : public QMainWindow
{
    Q_OBJECT

public:
    explicit KastiBob(QWidget *parent = 0);
    ~KastiBob();

private:
    Ui::KastiBob *ui;
};

#endif // KASTIBOB_H
