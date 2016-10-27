/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEksportuj;
    QAction *actionImportuj;
    QAction *actionWyjd;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *progressBar;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QProgressBar *progressBar_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QProgressBar *progressBar_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_11;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menuBar;
    QMenu *menuKastiBob;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(418, 427);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionEksportuj = new QAction(MainWindow);
        actionEksportuj->setObjectName(QStringLiteral("actionEksportuj"));
        actionImportuj = new QAction(MainWindow);
        actionImportuj->setObjectName(QStringLiteral("actionImportuj"));
        actionWyjd = new QAction(MainWindow);
        actionWyjd->setObjectName(QStringLiteral("actionWyjd"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_7);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        label_6->setFont(font);

        horizontalLayout_13->addWidget(label_6);


        horizontalLayout_9->addWidget(groupBox_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        groupBox_8 = new QGroupBox(groupBox_2);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_14 = new QHBoxLayout(groupBox_8);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label = new QLabel(groupBox_8);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label);


        horizontalLayout_9->addWidget(groupBox_8);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_12 = new QHBoxLayout(groupBox_6);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_12->addWidget(label_13);


        horizontalLayout_9->addWidget(groupBox_6);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_4);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(127, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setStyleSheet(QLatin1String("\n"
"\n"
" QProgressBar::chunk {\n"
"     background-color: rgb(255, 0, 0);\n"
"     width: 20px;\n"
" }"));
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);


        horizontalLayout_7->addLayout(verticalLayout_2);


        horizontalLayout_10->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_3 = new QVBoxLayout(groupBox_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);


        horizontalLayout_8->addLayout(horizontalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(183, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_8);

        progressBar_2 = new QProgressBar(groupBox_5);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setStyleSheet(QLatin1String("\n"
" QProgressBar::chunk {\n"
"     background-color:rgb(0, 0, 255);\n"
"     width: 20px;\n"
" }"));
        progressBar_2->setValue(24);

        verticalLayout_3->addWidget(progressBar_2);


        horizontalLayout_10->addWidget(groupBox_5);


        verticalLayout_4->addLayout(horizontalLayout_10);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_2->addWidget(label_8);

        progressBar_3 = new QProgressBar(groupBox_3);
        progressBar_3->setObjectName(QStringLiteral("progressBar_3"));
        progressBar_3->setStyleSheet(QLatin1String("\n"
" QProgressBar::chunk {\n"
"     background-color:rgb(0, 170, 0);\n"
"     width: 20px;\n"
" }"));
        progressBar_3->setValue(24);

        horizontalLayout_2->addWidget(progressBar_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout->addWidget(label_9);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout->addWidget(label_10);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout->addWidget(label_11);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout->addWidget(label_12);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_4->addWidget(groupBox_3);


        verticalLayout_5->addWidget(groupBox_2);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_5);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 0, 1, 1);


        horizontalLayout_11->addWidget(groupBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 418, 21));
        menuKastiBob = new QMenu(menuBar);
        menuKastiBob->setObjectName(QStringLiteral("menuKastiBob"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton, pushButton_4);
        QWidget::setTabOrder(pushButton_4, pushButton_3);
        QWidget::setTabOrder(pushButton_3, pushButton_6);

        menuBar->addAction(menuKastiBob->menuAction());
        menuKastiBob->addAction(actionEksportuj);
        menuKastiBob->addAction(actionImportuj);
        menuKastiBob->addSeparator();
        menuKastiBob->addAction(actionWyjd);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_6, SIGNAL(clicked()), groupBox_2, SLOT(hide()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "KastiBob", 0));
        actionEksportuj->setText(QApplication::translate("MainWindow", "Eksportuj", 0));
        actionImportuj->setText(QApplication::translate("MainWindow", "Importuj", 0));
        actionWyjd->setText(QApplication::translate("MainWindow", "Wyjd\305\272", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Character info: ", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Nick: ", 0));
        label_6->setText(QApplication::translate("MainWindow", "Sajoch tu ma byc 32 znaki miesci", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Ping: ", 0));
        label->setText(QApplication::translate("MainWindow", "9999", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Profesja: ", 0));
        label_13->setText(QApplication::translate("MainWindow", "ED", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Hit Points: ", 0));
        label_4->setText(QApplication::translate("MainWindow", "1000", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Mana Points: ", 0));
        label_5->setText(QApplication::translate("MainWindow", "10000", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Level: ", 0));
        label_8->setText(QApplication::translate("MainWindow", "100", 0));
        label_9->setText(QApplication::translate("MainWindow", "Exp: ", 0));
        label_10->setText(QApplication::translate("MainWindow", "1234567890", 0));
        label_11->setText(QApplication::translate("MainWindow", "Exp/h: ", 0));
        label_12->setText(QApplication::translate("MainWindow", "1234567", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Menu: ", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Healer", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Hotheys", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Cavebot", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Alarm", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "xd", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Runemaker", 0));
        menuKastiBob->setTitle(QApplication::translate("MainWindow", "Plik", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
