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

void Setting::quick_type_unit_type()
{
    QString in=QFileDialog::getOpenFileName(this,"open","/");

    if(in.isEmpty()){
        return ;
    }

    ui->link_set->setText(in);
}

void Setting::when_button_accepted()
{
    pre_link=ui->link_set->text();
    pre_type=ui->unit_link_set->currentText();
    if(pre_type!="none"&&!pre_type.isEmpty()){
        link_set.insert(pre_type,pre_link);
    }

    emit readpath(ui->localization->text(),ui->resource->text(),link_set);
    //emit readpath("111","222");

    this->close();
}

void Setting::change_link_set()
{
    if(pre_type!="none"&&!pre_type.isEmpty()){
        link_set.insert(pre_type,pre_link);
    }

    pre_link=ui->link_set->text();
    pre_type=ui->unit_link_set->currentText();


}
