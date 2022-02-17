#include "setting.h"
#include "ui_setting.h"

#include <QFileDialog>

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowTitle("Setting");
}

Setting::~Setting()
{
    delete ui;
}

void Setting::quick_type_local()
{
    QString in=QFileDialog::getExistingDirectory(this,"open","/");

    if(in.isEmpty()){
        return ;
    }

    ui->localization->setText(in);
}

void Setting::quick_type_res()
{
    QString in=QFileDialog::getExistingDirectory(this,"open","/");

    if(in.isEmpty()){
        return ;
    }

    ui->resource->setText(in);
}

void Setting::when_button_accepted()
{
    emit readpath(ui->localization->text(),ui->resource->text());
    //emit readpath("111","222");

    this->close();
}
