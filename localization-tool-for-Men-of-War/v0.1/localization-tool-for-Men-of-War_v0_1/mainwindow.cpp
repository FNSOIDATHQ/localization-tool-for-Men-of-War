#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("localization tool for Men of War v0.01");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readpath()
{
    QString resource_path,localization_path;
    resource_path=ui->resource->text();
    localization_path=ui->localization->text();

    ui->label_3->setText(resource_path);
    ui->label_4->setText(localization_path);
}
