#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDialog>
#include <QDir>
#include <QTreeWidget>
#include <QMessageBox>

//#include <QDebug>

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

        QDir breed_path,weapon_path,unit_path,stuff_path;
        unit_path=res;
        unit_path.cd("entity");
        unit_path.cd("-vehicle");
        breed_path=res;
        breed_path.cd("set");
        weapon_path=breed_path;
        breed_path.cd("breed");
        weapon_path.cd("stuff");
        stuff_path=weapon_path;

        read_unit_universal(breed_path,breed,"set");

        read_unit_universal(weapon_path,weapon,"weapon");

        read_unit_universal(unit_path,unit,"def");

        if(stuff_path.cd("head")){//必须依次按目录添加
            read_unit_universal(stuff_path,stuff,"");
            stuff_path.cdUp();
        }
        if(stuff_path.cd("body")){
            read_unit_universal(stuff_path,stuff,"");
            stuff_path.cdUp();
        }
        if(stuff_path.cd("explosive")){
            read_unit_universal(stuff_path,stuff,"");
            stuff_path.cdUp();
        }
        if(stuff_path.cd("grenade")){
            read_unit_universal(stuff_path,stuff,"grenade");
            stuff_path.cdUp();
        }
        if(stuff_path.cd("capacity")){
            read_unit_universal(stuff_path,stuff,"");
            stuff_path.cdUp();
        }
        if(stuff_path.cd("special")){
            read_unit_universal(stuff_path,stuff,"");
            stuff_path.cdUp();
        }

        QString cur_show=ui->unit_type->currentText();

        change_show_box(cur_show);

        //ui->breed_list->addItems(breed);

    }


}

void MainWindow::change_show_box(QString cur_show)
{
    if(cur_show=="breed"){
        create_tree(breed,"breed",6);
        cur_type=&breed;
    }
    else if(cur_show=="stuff"){
        create_tree(stuff,"stuff",6);
        cur_type=&stuff;
    }
    else if(cur_show=="weapon"){
        create_tree(weapon,"stuff",6);
        cur_type=&weapon;
    }
    else if(cur_show=="unit"){
        create_tree(unit,"-vehicle",9);
        cur_type=&unit;
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


    //qDebug()<<ori_y;

}

void MainWindow::save_cur_unit()
{
    bool temp_b2=cur_select->data().value<unit_data>().b_need_localize;
    int temp_index=cur_select->data().value<unit_data>().index;
    QString temp_text=ui->edit_unit->toPlainText();
    unit_data_update(temp_b2,temp_index,temp_text);
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

    if(cur_select->data().value<unit_data>().b_need_localize==true){
        ui->check_is_need_localize->setChecked(true);
    }
    else{
        ui->check_is_need_localize->setChecked(false);
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

void MainWindow::change_localize_state()
{
    bool temp_b2;

    if(cur_select->data().value<unit_data>().b_need_localize==true){
        temp_b2=false;
        ui->check_is_need_localize->setChecked(false);
    }
    else{
        temp_b2=true;
        ui->check_is_need_localize->setChecked(true);

    }
    int temp_index=cur_select->data().value<unit_data>().index;
    QString temp_text=cur_select->data().value<unit_data>().text;
    unit_data_update(temp_b2,temp_index,temp_text);
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

int MainWindow::create_tree(QFileInfoList tar,QString tar_type,int path_length)
{
    Tree_Data->clear();//这是一个临时措施

    for(int i=0;i<tar.size();i++){
        //qDebug() <<tar.at(i).filePath();
        QString path=tar.at(i).filePath();//获取文件的完整路径（包括文件名）

        path=path.mid(path.indexOf(tar_type)+path_length);

        QStringList path_splited=path.split("/");


        for(int i=0;i<path_splited.size();i++){
            bool is_need_add=true;

            //if(Tree_Data->findItems(path_splited[i],Qt::MatchExactly,i).isEmpty()){//如果没有找到对应项
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
                TempFindList=Tree_Data->findItems(path_splited[0],Qt::MatchExactly,0);
                QStandardItem* cur_item;


                if(!TempFindList.empty()){
                    cur_item=TempFindList[0];

                    if(i!=0){//如果有上一级，就检查上一级是否存在
                        for(int j=1;j<=i;j++){
                            int child_index=0;

                            while(cur_item->child(child_index)){//遍历下一层，找到和数据相同的下一个节点
                                if(cur_item->child(child_index)->text()==path_splited[j]){
                                    //qDebug()<<"1";
                                    break;
                                }
                                child_index++;
                            }

                            if(!cur_item->child(child_index)){//如果当前节点没东西，说明没找到下一个
                                //qDebug()<<1;
                                break;
                            }
                            else if(j==i){//此时说明匹配到了，而且是当前要添加的节点匹配到了，那么就应该立刻弹出
                                //qDebug()<<2;
                                is_need_add=false;
                            }
                            else{
                                //qDebug()<<3;
                                cur_item=cur_item->child(child_index);
                            }
                        }

                    }
                    else{
                        if(cur_item->text()==path_splited[i]){
                            is_need_add=false;
                        }
                    }

                }



                //qDebug()<<QString::number(is_need_add);
                if(!is_need_add){
                    continue;

                }
                else if(TempFindList.empty()){

                    Tree_Data->appendRow(temp);

                }
                else if(cur_item->text()!=path_splited[i-1]){//如果没有找到上一级，说明它就是底层

                    Tree_Data->appendRow(temp);

                }
                else{//如果有上一级，就连接到上一级
                    //qDebug()<<4;
                    QStandardItem* temp_upst=cur_item;
                    temp_upst->appendRow(temp);

                }



            //}

        }
    }


    return 0;
}
