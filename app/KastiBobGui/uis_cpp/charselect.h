/********************************************************************************
** Form generated from reading UI file 'charselect.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CharSelect
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *CharSelect)
    {
        if (CharSelect->objectName().isEmpty())
            CharSelect->setObjectName(QStringLiteral("CharSelect"));
        CharSelect->resize(215, 90);
        gridLayout = new QGridLayout(CharSelect);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(CharSelect);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(CharSelect);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(comboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_2 = new QPushButton(CharSelect);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(CharSelect);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(CharSelect);

        QMetaObject::connectSlotsByName(CharSelect);
    } // setupUi

    void retranslateUi(QDialog *CharSelect)
    {
        CharSelect->setWindowTitle(QApplication::translate("CharSelect", "Dialog", 0));
        label->setText(QApplication::translate("CharSelect", "logged", 0));
        pushButton_2->setText(QApplication::translate("CharSelect", "Enter", 0));
        pushButton->setText(QApplication::translate("CharSelect", "Logout", 0));
    } // retranslateUi

};

namespace Ui {
    class CharSelect: public Ui_CharSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CHARSELECT_H
