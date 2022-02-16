/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionsettings;
    QAction *actionsave;
    QAction *actionredo;
    QAction *actionexit;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *localization;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *resource;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QMenu *menuedit;
    QMenu *menufile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionsettings = new QAction(MainWindow);
        actionsettings->setObjectName(QString::fromUtf8("actionsettings"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionredo = new QAction(MainWindow);
        actionredo->setObjectName(QString::fromUtf8("actionredo"));
        actionexit = new QAction(MainWindow);
        actionexit->setObjectName(QString::fromUtf8("actionexit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 30, 721, 189));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(67);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        localization = new QLineEdit(verticalLayoutWidget);
        localization->setObjectName(QString::fromUtf8("localization"));

        horizontalLayout_6->addWidget(localization);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(100);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(false);

        horizontalLayout_8->addWidget(label);

        resource = new QLineEdit(verticalLayoutWidget);
        resource->setObjectName(QString::fromUtf8("resource"));

        horizontalLayout_8->addWidget(resource);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_5->setContentsMargins(100, -1, 100, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_5);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 240, 431, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 280, 431, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuedit = new QMenu(menubar);
        menuedit->setObjectName(QString::fromUtf8("menuedit"));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menuedit->menuAction());
        menuedit->addAction(actionsettings);
        menufile->addAction(actionsave);
        menufile->addAction(actionredo);
        menufile->addAction(actionexit);

        retranslateUi(MainWindow);
        QObject::connect(actionexit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(pressed()), MainWindow, SLOT(readpath()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionsettings->setText(QCoreApplication::translate("MainWindow", "settings", nullptr));
        actionsave->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
#if QT_CONFIG(shortcut)
        actionsave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionredo->setText(QCoreApplication::translate("MainWindow", "redo", nullptr));
        actionexit->setText(QCoreApplication::translate("MainWindow", "exit", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "set localization path:", nullptr));
        localization->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "set resource path:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuedit->setTitle(QCoreApplication::translate("MainWindow", "edit", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
