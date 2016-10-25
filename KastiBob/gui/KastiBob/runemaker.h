#ifndef RUNEMAKER_H
#define RUNEMAKER_H

#include <QDialog>

namespace Ui {
class Runemaker;
}

class Runemaker : public QDialog
{
    Q_OBJECT

public:
    explicit Runemaker(QWidget *parent = 0);
    ~Runemaker();

private:
    Ui::Runemaker *ui;
};

#endif // RUNEMAKER_H
