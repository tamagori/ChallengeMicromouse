/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QTextEdit *filePathEdit;
    QLabel *label;
    QTextEdit *actionHistoryEdit;
    QPushButton *loadButton;
    QPushButton *drawMazeButton;
    QLabel *label_2;
    QPushButton *SimulateStart;
    QPushButton *quitButton;
    QComboBox *SellSimuMode;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 30, 800, 800));
        filePathEdit = new QTextEdit(centralwidget);
        filePathEdit->setObjectName(QString::fromUtf8("filePathEdit"));
        filePathEdit->setEnabled(true);
        filePathEdit->setGeometry(QRect(860, 90, 251, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(940, 60, 111, 16));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        actionHistoryEdit = new QTextEdit(centralwidget);
        actionHistoryEdit->setObjectName(QString::fromUtf8("actionHistoryEdit"));
        actionHistoryEdit->setGeometry(QRect(860, 210, 291, 281));
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(1128, 90, 54, 41));
        drawMazeButton = new QPushButton(centralwidget);
        drawMazeButton->setObjectName(QString::fromUtf8("drawMazeButton"));
        drawMazeButton->setGeometry(QRect(940, 690, 131, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(900, 170, 201, 31));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        SimulateStart = new QPushButton(centralwidget);
        SimulateStart->setObjectName(QString::fromUtf8("SimulateStart"));
        SimulateStart->setGeometry(QRect(940, 740, 131, 41));
        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        quitButton->setGeometry(QRect(1090, 791, 93, 41));
        SellSimuMode = new QComboBox(centralwidget);
        SellSimuMode->setObjectName(QString::fromUtf8("SellSimuMode"));
        SellSimuMode->setGeometry(QRect(860, 560, 291, 41));
        SellSimuMode->setLayoutDirection(Qt::LeftToRight);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(880, 530, 241, 16));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Load File", nullptr));
        loadButton->setText(QApplication::translate("MainWindow", "...", nullptr));
        drawMazeButton->setText(QApplication::translate("MainWindow", "Draw Maze", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Action History", nullptr));
        SimulateStart->setText(QApplication::translate("MainWindow", "Simulate Start", nullptr));
        quitButton->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Select Simulate Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
