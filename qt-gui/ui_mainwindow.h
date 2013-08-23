/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *teachButton;
    QPushButton *testButton;
    QLabel *imgView;
    QListWidget *pathList;
    QMenuBar *menuBar;
    QMenu *menuKohonen_Neural_Netword_Self_orginized_map;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(484, 269);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        teachButton = new QPushButton(centralWidget);
        teachButton->setObjectName(QString::fromUtf8("teachButton"));
        teachButton->setGeometry(QRect(210, 200, 111, 21));
        testButton = new QPushButton(centralWidget);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(340, 200, 121, 24));
        imgView = new QLabel(centralWidget);
        imgView->setObjectName(QString::fromUtf8("imgView"));
        imgView->setGeometry(QRect(50, 0, 181, 161));
        pathList = new QListWidget(centralWidget);
        pathList->setObjectName(QString::fromUtf8("pathList"));
        pathList->setGeometry(QRect(210, 0, 256, 192));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 484, 21));
        menuKohonen_Neural_Netword_Self_orginized_map = new QMenu(menuBar);
        menuKohonen_Neural_Netword_Self_orginized_map->setObjectName(QString::fromUtf8("menuKohonen_Neural_Netword_Self_orginized_map"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuKohonen_Neural_Netword_Self_orginized_map->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        teachButton->setText(QApplication::translate("MainWindow", "Teach", 0, QApplication::UnicodeUTF8));
        testButton->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
        imgView->setText(QString());
        menuKohonen_Neural_Netword_Self_orginized_map->setTitle(QApplication::translate("MainWindow", "Kohonen Neural Network. Self-orginized map.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
