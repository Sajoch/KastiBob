/********************************************************************************
** Form generated from reading UI file 'gejm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEJM_H
#define UI_GEJM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Gejm
{
public:

    void setupUi(QDialog *Gejm)
    {
        if (Gejm->objectName().isEmpty())
            Gejm->setObjectName(QStringLiteral("Gejm"));
        Gejm->resize(400, 300);

        retranslateUi(Gejm);

        QMetaObject::connectSlotsByName(Gejm);
    } // setupUi

    void retranslateUi(QDialog *Gejm)
    {
        Gejm->setWindowTitle(QApplication::translate("Gejm", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Gejm: public Ui_Gejm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEJM_H
