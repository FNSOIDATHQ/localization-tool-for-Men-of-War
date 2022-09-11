//#include "mainwindow.h"
#include "selectdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w;

    //w.show();

    SelectDialog intro;

    intro.show();
    return a.exec();
}
