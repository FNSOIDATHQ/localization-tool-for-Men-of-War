#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("localization tool for Men of War v0.01");

    setting= new Setting();

    connect(setting,SIGNAL(readpath(QString, QString)),this,SLOT(getpath(QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getpath(QString local, QString res)
{
    ui->label_3->setText(local);
    ui->label_4->setText(res);
}

void MainWindow::open_setting()
{
    setting->show();
}

