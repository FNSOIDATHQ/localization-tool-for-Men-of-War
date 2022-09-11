#include "lng2csv_tool.h"
#include "ui_lng2csv_tool.h"

#include <QFile>
#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>

//#include <QDebug>

lng2csv_tool::lng2csv_tool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lng2csv_tool)
{
    ui->setupUi(this);

    setWindowTitle("lng/csv转换工具 v0.01");
}

lng2csv_tool::~lng2csv_tool()
{
    delete ui;
}


void lng2csv_tool::quick_type_lng()
{
    QString in=QFileDialog::getOpenFileName(this,"open","/");

    if(in.isEmpty()){
        return ;
    }

    ui->lng_path->setText(in);
}


void lng2csv_tool::read_lng_file(){
    QString file_in=ui->lng_path->text();

    //QTextCodec *codec = QTextCodec::codecForName("utf-8");

    QFile file(file_in);
    if(file.open(QIODevice::ReadOnly)){
        file_name=file.fileName();
        file_name.remove(file_name.length() - 4, 4);
        file_name.append(".csv");


        ui->PreviewBrowser->clear();
        while(!file.atEnd()){

        //for(int i=0;i<10;i++){
            QByteArray line=file.readLine();//这是一个偷懒的办法，可以避免从头建立树结构。但是也意味着如果本地化文件不工整读取就会出错
            QString line_string(line);
            QString key,pre_loc;
            //ui->PreviewBrowser->append(line_string);



            for(int i=0;i<line_string.size();i++){
                QChar now=line_string.at(i);

                if(now==';'){//分号后内容均为注释
                    //ui->PreviewBrowser->append("检测到注释！");
                    break;
                }
                else if(now=='"'){
                    if(key.isEmpty()){//如果key里没有值，说明即将录入key
                        i++;
                        key.append("\"key_");
                        while(line_string.at(i)!='"'){
                            key.append(line_string.at(i));
                            i++;
                        }
                        key.append('"');
                    }
                    else {//那么说明即将录入pre_loc
                        i++;
                        pre_loc.append('"');
                        while(line_string.at(i)!='"'){
                            pre_loc.append(line_string.at(i));
                            i++;
                        }
                        pre_loc.append('"');
                    }
                }
                else if(now=='}'){//存在后括号说明本行为1.要本地化的字串2.一个树的结尾
                    //qDebug()<<key<<' '<<pre_loc<<endl;
                    if(!key.isEmpty()&&!pre_loc.isEmpty()){//说明情况为1
                        ui->PreviewBrowser->append(key+","+pre_loc+",");//插入csv
                    }
                    break;
                }
            }
        }

        file.close();
    }
    else{
        QMessageBox *msgBox;
            msgBox = new QMessageBox("警告",
                "找不到文件或路径格式不正确！",
                QMessageBox::Critical,
                QMessageBox::Ok | QMessageBox::Default,
                QMessageBox::Cancel | QMessageBox::Escape,
                0);

            msgBox->show();
    }

}

void lng2csv_tool::save_csv_file(){
    QString save_fullpath=QFileDialog::getSaveFileName(this,"Save",file_name,"csv(*csv)");

    QFile tar_file(save_fullpath);


    if(tar_file.open(QIODevice::WriteOnly|QIODevice::Text)){//如果顺利打开
        QString text=ui->PreviewBrowser->toPlainText();

        QByteArray in_data=text.toUtf8();

        tar_file.write(in_data);
    }
}

//D:/steam/steamapps/common/Men of War Assault Squad 2/mods/wzss-eastern_asia_pack_v0_7_5/localization/#dlg_frontend.lng
