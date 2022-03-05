#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDialog>
#include <QDir>
#include <QTreeWidget>
#include <QMessageBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("localization tool for Men of War v0.01");

    setting= new Setting();

    Tree_Data=new QStandardItemModel();

    ui->unit_tree->setModel(Tree_Data);

    //ui->unit_tree->verticalScrollBar()->setDisabled(true);


    Tree_Data->setHorizontalHeaderLabels(QStringList()<<"Unit Tree");

    pre_value=0;
    unit_num=0;

    ori_y=ui->unit_tree->height();

    //ui->check_is_modifed->setCheckable(false);//禁止用户点击

    connect(setting,SIGNAL(readpath(QString, QString,QMap<QString,QString>)),this,SLOT(getpath(QString, QString,QMap<QString,QString>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getpath(QString local, QString res,QMap<QString,QString> link)
{
    res_path=res;
    local_path=local;
    localize_link=link;
}

void MainWindow::open_setting()
{
    setting->show();
}

void MainWindow::read_unit()
{
    res.setPath(res_path);

    if(res.exists()){
        res.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

        res.setSorting(QDir::DirsFirst);

        QDir breed_path,stuff_path;
        breed_path=res;
        breed_path.cd("set");
        stuff_path=breed_path;
        breed_path.cd("breed");
        stuff_path.cd("stuff");

        read_unit_universal(breed_path,breed,"set");

        read_unit_universal(stuff_path,stuff,"weapon");

        QString cur_show=ui->unit_type->currentText();

        change_show_box(cur_show);

        //ui->breed_list->addItems(breed);

    }


}

void MainWindow::change_show_box(QString cur_show)
{
    if(cur_show=="breed"){
        create_tree(breed,"breed");
        cur_type=&breed;
    }
    else if(cur_show=="stuff"){
        create_tree(stuff,"stuff");
        cur_type=&stuff;
    }

    Tree_Data->setHorizontalHeaderLabels(QStringList()<<"Unit Tree");//我不知道有没有更好的办法来保持标题不变




}

void MainWindow::scrollbar_move(int value)//外置滚动条
{
    //double precent=static_cast<double>(value)/static_cast<double>(ui->verticalScrollBar->maximum());
    //pre_precent=static_cast<double>(value)/static_cast<double>(ui->verticalScrollBar->maximum());

    //double precent=

    int cur_rate=value-pre_value;
    pre_value=value;
    //ui->unit_tree->setGeometry(ui->unit_tree->x(),ui->unit_tree->y(),ui->unit_tree->width(),ui->unit_tree->height());
    //if(ui->unit_tree->y()+cur_rate<ori_y){
    //    ui->unit_tree->scroll(ui->unit_tree->x(),ui->unit_tree->y()+cur_rate);
    //}
    //ui->unit_tree->scrollTo(Tree_Data->index(0,value));

    //ui->unit_tree->scrollToBottom();


    qDebug()<<ori_y;

}

void MainWindow::save_cur_unit()
{
    bool temp_b2=cur_select->data().value<unit_data>().b_need_localize;
    int temp_index=cur_select->data().value<unit_data>().index;
    QString tenp_text=ui->edit_unit->toPlainText();
    unit_data_update(temp_b2,temp_index,tenp_text);
    refresh_unit_edit();

}

void MainWindow::show_unit(QModelIndex selected)
{
    cur_select=Tree_Data->itemFromIndex(selected);

    if(cur_select->data().value<unit_data>().b_is_modifed==true){
        ui->check_is_modifed->setChecked(true);
    }
    else{
        ui->check_is_modifed->setChecked(false);
    }

    refresh_unit_edit();
    //ui->check_is_modifed->setChecked(true);


}

void MainWindow::save_current_type()
{
    //QString save_fullpath=QFileDialog::getOpenFileName(this,"open","/");

    QString save_fullpath=QFileDialog::getSaveFileName(this,"open","/");

    QFile tar_file(save_fullpath);

    //if(tar_file.exists()){
    //    QMessageBox::warning(this,"Create File","File is already exist!");
    //}
    //else{
        if(tar_file.open(QIODevice::ReadWrite|QIODevice::Text)){//如果顺利打开
            QString cur_local,final_save;
            for(int i=0;i<cur_type->size();i++){
                QString cur_tar=cur_type->at(i).fileName();
                QString cur_tar_save_name=cur_type->at(i).baseName();
                cur_local=Tree_Data->findItems(cur_tar,Qt::MatchContains|Qt::MatchRecursive)[0]->data().value<unit_data>().text;//通过名字索引内容
                final_save+="{\""+cur_tar_save_name+"\" \""+cur_local+"\"}\n";
            }

            QByteArray in_data=final_save.toUtf8();

            tar_file.write(in_data);

        }
    //}
}

void MainWindow::refresh_unit_edit()
{
    ui->edit_unit->setText(cur_select->data().value<unit_data>().text);
}

void MainWindow::unit_data_update(bool b_need_localize, int index, QString text)
{
    QVariant temp_data;
    unit_data temp_data_value;
    temp_data_value.index=index;
    temp_data_value.b_is_modifed=true;//只要运行了这个函数，就一定修改过了
    ui->check_is_modifed->setChecked(true);
    temp_data_value.b_need_localize=b_need_localize;
    temp_data_value.text=text;
    temp_data=QVariant::fromValue(temp_data_value);

    cur_select->setData(temp_data);
}


int MainWindow::read_unit_universal(QDir path,QFileInfoList &tar,QString suffix_Filter){
    if(!path.exists()){
        return -1;
    }

    path.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

    path.setSorting(QDir::DirsFirst);

    QFileInfoList info=path.entryInfoList();

    for(int i=0;i<info.size();i++){
        QFileInfo cur=info.at(i);
        if(cur.isDir()){//如果是文件夹，就递归，进入文件夹继续查找
            read_unit_universal(cur.filePath(),tar,suffix_Filter);
        }
        else{
            while(i<info.size()){
                cur=info.at(i);

                if(info.at(i).suffix()==suffix_Filter){
                    tar.push_back(cur);
                }
                i++;

            }
        }
    }

    return 0;
}

int MainWindow::create_tree(QFileInfoList tar,QString tar_type)
{
    Tree_Data->clear();//这是一个临时措施

    for(int i=0;i<tar.size();i++){
        //qDebug() <<tar.at(i).filePath();
        QString path=tar.at(i).filePath();//获取文件的完整路径（包括文件名）

        path=path.mid(path.indexOf(tar_type)+6);

        QStringList path_splited=path.split("/");


        for(int i=0;i<path_splited.size();i++){

            if(Tree_Data->findItems(path_splited[i],Qt::MatchContains|Qt::MatchRecursive).isEmpty()){//如果没有找到对应项
                QStandardItem *temp=new QStandardItem(path_splited[i]);
                    QVariant temp_data;//不管是不是真的需要本地化，都必须添加标签
                    unit_data temp_data_value;
                    temp_data_value.b_is_modifed=false;
                    temp_data_value.index=-1;//如果是-1，说明这里存储的是个路径
                    temp_data_value.b_need_localize=false;
                    if(i==path_splited.size()-1){//如果是需要本地化是词条而不是目录，则添加一个需要本地化的标志
                        temp_data_value.index=unit_num++;
                        temp_data_value.b_need_localize=true;
                        temp_data_value.text="none";
                    }
                    temp_data=QVariant::fromValue(temp_data_value);
                    temp->setData(temp_data);
                    //qDebug()<<temp->data().value<unit_data>().text;


                QList<QStandardItem*> TempFindList;
                if(i!=0){//如果有上一级，就检查上一级是否存在
                   TempFindList=Tree_Data->findItems(path_splited[i-1],Qt::MatchContains|Qt::MatchRecursive);
                }

                if(TempFindList.isEmpty()){//如果没有找到上一级，说明它就是底层

                    Tree_Data->appendRow(temp);
                }
                else{//如果有上一级，就连接到上一级
                    QStandardItem* temp_upst=TempFindList[0];
                    temp_upst->appendRow(temp);
                }



            }

        }
    }


    return 0;
}
