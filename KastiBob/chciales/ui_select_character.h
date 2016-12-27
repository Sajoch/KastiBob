/********************************************************************************
** Form generated from reading UI file 'select_character.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_CHARACTER_H
#define UI_SELECT_CHARACTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Select_character
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Select_character)
    {
        if (Select_character->objectName().isEmpty())
            Select_character->setObjectName(QStringLiteral("Select_character"));
        Select_character->resize(239, 264);
        horizontalLayout_3 = new QHBoxLayout(Select_character);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox = new QGroupBox(Select_character);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addWidget(groupBox);


        retranslateUi(Select_character);

        QMetaObject::connectSlotsByName(Select_character);
    } // setupUi

    void retranslateUi(QDialog *Select_character)
    {
        Select_character->setWindowTitle(QApplication::translate("Select_character", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Select_character", "Select Character", 0));
        pushButton->setText(QApplication::translate("Select_character", "Ok", 0));
        pushButton_2->setText(QApplication::translate("Select_character", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class Select_character: public Ui_Select_character {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_CHARACTER_H
