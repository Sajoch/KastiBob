/********************************************************************************
** Form generated from reading UI file 'trainer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAINER_H
#define UI_TRAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Trainer
{
public:
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_6;
    QProgressBar *progressBar;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *Trainer)
    {
        if (Trainer->objectName().isEmpty())
            Trainer->setObjectName(QStringLiteral("Trainer"));
        Trainer->resize(293, 335);
        horizontalLayout_10 = new QHBoxLayout(Trainer);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(Trainer);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(99999);

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_2->addWidget(label_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_2->addWidget(checkBox_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        groupBox_4 = new QGroupBox(Trainer);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_4);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QLatin1String("\n"
" QProgressBar::chunk {\n"
"     background-color:rgb(255, 170, 0);\n"
"     width: 20px;\n"
" }"));
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);


        horizontalLayout_6->addLayout(verticalLayout_2);


        horizontalLayout_9->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(Trainer);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_7->addWidget(checkBox);


        horizontalLayout_9->addWidget(groupBox_2);


        verticalLayout_3->addLayout(horizontalLayout_9);

        groupBox_3 = new QGroupBox(Trainer);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_3);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_8->addWidget(label_10);

        textBrowser = new QTextBrowser(groupBox_3);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout_8->addWidget(textBrowser);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_10->addLayout(verticalLayout_3);


        retranslateUi(Trainer);

        QMetaObject::connectSlotsByName(Trainer);
    } // setupUi

    void retranslateUi(QDialog *Trainer)
    {
        Trainer->setWindowTitle(QApplication::translate("Trainer", "Trainer", 0));
        groupBox->setTitle(QApplication::translate("Trainer", "Runes: ", 0));
        label->setText(QApplication::translate("Trainer", "Spell:", 0));
        label_4->setText(QApplication::translate("Trainer", "Mana:", 0));
        label_5->setText(QApplication::translate("Trainer", "Runes made: ", 0));
        label_6->setText(QApplication::translate("Trainer", "100", 0));
        label_7->setText(QApplication::translate("Trainer", "Blank runes: ", 0));
        label_8->setText(QApplication::translate("Trainer", "100", 0));
        checkBox_2->setText(QApplication::translate("Trainer", "Train", 0));
        groupBox_4->setTitle(QApplication::translate("Trainer", "Magic level: ", 0));
        label_2->setText(QApplication::translate("Trainer", "Magic level: ", 0));
        label_3->setText(QApplication::translate("Trainer", "100", 0));
        groupBox_2->setTitle(QApplication::translate("Trainer", "Auto-eater: ", 0));
        checkBox->setText(QString());
        groupBox_3->setTitle(QApplication::translate("Trainer", "Fishing: ", 0));
        label_10->setText(QApplication::translate("Trainer", "tutej jezdze cuz bedzie", 0));
        textBrowser->setHtml(QApplication::translate("Trainer", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ale nie wiem co</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ale bedzie</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Trainer: public Ui_Trainer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAINER_H
