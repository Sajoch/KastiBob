/********************************************************************************
** Form generated from reading UI file 'healer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEALER_H
#define UI_HEALER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Healer
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;
    QSpinBox *spinBox_7;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_9;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_4;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_8;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_12;
    QLabel *label_13;
    QSpinBox *spinBox_10;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QLabel *label_14;
    QSpinBox *spinBox_11;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_17;
    QLabel *label_19;
    QSpinBox *spinBox_15;
    QVBoxLayout *verticalLayout;
    QLabel *label_16;
    QLabel *label_18;
    QSpinBox *spinBox_12;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_9;
    QSpinBox *spinBox_13;
    QSpinBox *spinBox_14;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QSpinBox *spinBox_16;
    QSpinBox *spinBox_17;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_11;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;

    void setupUi(QDialog *Healer)
    {
        if (Healer->objectName().isEmpty())
            Healer->setObjectName(QStringLiteral("Healer"));
        Healer->resize(321, 357);
        horizontalLayout_3 = new QHBoxLayout(Healer);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        groupBox = new QGroupBox(Healer);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_10 = new QVBoxLayout(groupBox);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_6->addWidget(label);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(3);

        verticalLayout_6->addWidget(spinBox);

        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(3);

        verticalLayout_6->addWidget(spinBox_2);

        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(3);

        verticalLayout_6->addWidget(spinBox_3);


        horizontalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_7->addWidget(label_2);

        spinBox_7 = new QSpinBox(groupBox);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setMaximum(99999);

        verticalLayout_7->addWidget(spinBox_7);

        spinBox_6 = new QSpinBox(groupBox);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setMaximum(99999);

        verticalLayout_7->addWidget(spinBox_6);

        spinBox_9 = new QSpinBox(groupBox);
        spinBox_9->setObjectName(QStringLiteral("spinBox_9"));
        spinBox_9->setMaximum(99999);

        verticalLayout_7->addWidget(spinBox_9);


        horizontalLayout_9->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_8->addWidget(label_4);

        spinBox_4 = new QSpinBox(groupBox);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMaximum(99999);

        verticalLayout_8->addWidget(spinBox_4);

        spinBox_5 = new QSpinBox(groupBox);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(99999);

        verticalLayout_8->addWidget(spinBox_5);

        spinBox_8 = new QSpinBox(groupBox);
        spinBox_8->setObjectName(QStringLiteral("spinBox_8"));
        spinBox_8->setMaximum(99999);

        verticalLayout_8->addWidget(spinBox_8);


        horizontalLayout_9->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_9->addWidget(label_3);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_9->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout_9->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout_9->addWidget(lineEdit_3);


        horizontalLayout_9->addLayout(verticalLayout_9);


        verticalLayout_10->addLayout(horizontalLayout_9);


        verticalLayout_11->addWidget(groupBox);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        groupBox_2 = new QGroupBox(Healer);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_13->addWidget(label_12);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_13->addWidget(label_13);

        spinBox_10 = new QSpinBox(groupBox_2);
        spinBox_10->setObjectName(QStringLiteral("spinBox_10"));
        spinBox_10->setMaximum(99999);

        verticalLayout_13->addWidget(spinBox_10);


        horizontalLayout->addLayout(verticalLayout_13);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_3->addWidget(label_8);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_3->addWidget(label_14);

        spinBox_11 = new QSpinBox(groupBox_2);
        spinBox_11->setObjectName(QStringLiteral("spinBox_11"));
        spinBox_11->setMaximum(99999);

        verticalLayout_3->addWidget(spinBox_11);


        horizontalLayout->addLayout(verticalLayout_3);


        horizontalLayout_10->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(Healer);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_14->addWidget(label_17);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        verticalLayout_14->addWidget(label_19);

        spinBox_15 = new QSpinBox(groupBox_3);
        spinBox_15->setObjectName(QStringLiteral("spinBox_15"));
        spinBox_15->setMaximum(99999);

        verticalLayout_14->addWidget(spinBox_15);


        horizontalLayout_2->addLayout(verticalLayout_14);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout->addWidget(label_16);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        verticalLayout->addWidget(label_18);

        spinBox_12 = new QSpinBox(groupBox_3);
        spinBox_12->setObjectName(QStringLiteral("spinBox_12"));
        spinBox_12->setMaximum(99999);

        verticalLayout->addWidget(spinBox_12);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_10->addWidget(groupBox_3);


        verticalLayout_11->addLayout(horizontalLayout_10);

        groupBox_4 = new QGroupBox(Healer);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_4);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_2->addWidget(label_9);

        spinBox_13 = new QSpinBox(groupBox_4);
        spinBox_13->setObjectName(QStringLiteral("spinBox_13"));
        spinBox_13->setMaximum(99999);

        verticalLayout_2->addWidget(spinBox_13);

        spinBox_14 = new QSpinBox(groupBox_4);
        spinBox_14->setObjectName(QStringLiteral("spinBox_14"));
        spinBox_14->setMaximum(99999);

        verticalLayout_2->addWidget(spinBox_14);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_5->addWidget(label_10);

        spinBox_16 = new QSpinBox(groupBox_4);
        spinBox_16->setObjectName(QStringLiteral("spinBox_16"));
        spinBox_16->setMaximum(99999);

        verticalLayout_5->addWidget(spinBox_16);

        spinBox_17 = new QSpinBox(groupBox_4);
        spinBox_17->setObjectName(QStringLiteral("spinBox_17"));
        spinBox_17->setMaximum(99999);

        verticalLayout_5->addWidget(spinBox_17);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_4->addWidget(label_11);

        lineEdit_4 = new QLineEdit(groupBox_4);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout_4->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(groupBox_4);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        verticalLayout_4->addWidget(lineEdit_5);


        horizontalLayout_7->addLayout(verticalLayout_4);


        horizontalLayout_8->addLayout(horizontalLayout_7);


        verticalLayout_11->addWidget(groupBox_4);


        horizontalLayout_3->addLayout(verticalLayout_11);


        retranslateUi(Healer);

        QMetaObject::connectSlotsByName(Healer);
    } // setupUi

    void retranslateUi(QDialog *Healer)
    {
        Healer->setWindowTitle(QApplication::translate("Healer", "Healer", 0));
        groupBox->setTitle(QApplication::translate("Healer", "Spells: ", 0));
        label->setText(QApplication::translate("Healer", "Prio:", 0));
        label_2->setText(QApplication::translate("Healer", "HP:", 0));
        label_4->setText(QApplication::translate("Healer", "Mana:", 0));
        label_3->setText(QApplication::translate("Healer", "Text:", 0));
        groupBox_2->setTitle(QApplication::translate("Healer", "Potions: ", 0));
        label_12->setText(QApplication::translate("Healer", "Health Potion", 0));
        label_13->setText(QApplication::translate("Healer", "HP: ", 0));
        label_8->setText(QApplication::translate("Healer", "Mana Potion", 0));
        label_14->setText(QApplication::translate("Healer", "Mana:", 0));
        groupBox_3->setTitle(QApplication::translate("Healer", "Runes: ", 0));
        label_17->setText(QApplication::translate("Healer", "IH Rune", 0));
        label_19->setText(QApplication::translate("Healer", "HP: ", 0));
        label_16->setText(QApplication::translate("Healer", "UH Rune", 0));
        label_18->setText(QApplication::translate("Healer", "HP: ", 0));
        groupBox_4->setTitle(QApplication::translate("Healer", "Anty-Paralyze: ", 0));
        label_9->setText(QApplication::translate("Healer", "HP:", 0));
        label_10->setText(QApplication::translate("Healer", "Mana:", 0));
        label_11->setText(QApplication::translate("Healer", "Text:", 0));
    } // retranslateUi

};

namespace Ui {
    class Healer: public Ui_Healer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEALER_H
