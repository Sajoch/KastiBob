/********************************************************************************
** Form generated from reading UI file 'hotheys.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOTHEYS_H
#define UI_HOTHEYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Hotheys
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *Hotheys)
    {
        if (Hotheys->objectName().isEmpty())
            Hotheys->setObjectName(QStringLiteral("Hotheys"));
        Hotheys->resize(400, 300);
        pushButton = new QPushButton(Hotheys);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 90, 75, 23));

        retranslateUi(Hotheys);

        QMetaObject::connectSlotsByName(Hotheys);
    } // setupUi

    void retranslateUi(QDialog *Hotheys)
    {
        Hotheys->setWindowTitle(QApplication::translate("Hotheys", "Hotkeys", 0));
        pushButton->setText(QApplication::translate("Hotheys", "hetkeje", 0));
    } // retranslateUi

};

namespace Ui {
    class Hotheys: public Ui_Hotheys {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOTHEYS_H
