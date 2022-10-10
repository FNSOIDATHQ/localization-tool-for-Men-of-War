#include "lng2csv_tool.h"
#include "ui_lng2csv_tool.h"

#include <QFileDialog>
#include <QTextCodec>
#include <QMessageBox>

#include <QDebug>

lng2csv_tool::lng2csv_tool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lng2csv_tool)
{
    ui->setupUi(this);

    pre_path="C:/";

    setWindowTitle("lng/csv转换工具 v0.031");

    isCSVreaded=false;
}

lng2csv_tool::~lng2csv_tool()
{
    delete ui;
}


void lng2csv_tool::quick_type_file_path()
{
    QString in=QFileDialog::getOpenFileName(this,"open",pre_path,"lng(*lng *inc);;csv(*csv)");

    if(in.isEmpty()){
        return ;
    }

    pre_path = in;
    int nIndex = pre_path.lastIndexOf('/');
    pre_path = pre_path.left(nIndex);

    ui->lng_path->setText(in);
}


void lng2csv_tool::read_file(){

    QString file_in=ui->lng_path->text();

    QFile file(file_in);

    int readMode=ui->read_mode->currentIndex();

    QString suffix=QFileInfo(file_in).suffix();

    if(checklegal(file_in,readMode)){
        if(readMode==0){//导入原文到CSV

            read_ori_to_csv(&file,suffix);
        }
        else if(readMode==1){//导入翻译到csv
            read_loc_to_csv(&file,suffix);
        }
        else{//导入翻译到lng
            read_loc_to_lng(&file);
        }
    }


}

void lng2csv_tool::save_file(){

    int readMode=ui->read_mode->currentIndex();

    QString save_fullpath;

    if(readMode==0||readMode==1){
        save_fullpath=QFileDialog::getSaveFileName(this,"Save",file_name,"csv(*csv)");
    }
    else if(readMode==2){
        save_fullpath=QFileDialog::getSaveFileName(this,"Save",file_name,"lng(*lng)");
    }

    QFile tar_file(save_fullpath);


    if(tar_file.open(QIODevice::WriteOnly|QIODevice::Text)){//如果顺利打开
        QString text=ui->PreviewBrowser->toPlainText();

        QByteArray in_data=text.toUtf8();

        tar_file.write(in_data);
    }

}

bool lng2csv_tool::read_ori_to_csv(QFile* file,QString suffix)
{

    QString file_codec=ui->encoding->currentText();

    QTextCodec *codec = QTextCodec::codecForName(file_codec.toUtf8());

    if(file->open(QIODevice::ReadOnly)){
        file_name=file->fileName();
        file_name.remove(file_name.length() - 4, 4);
        file_name.append(".csv");


        ui->PreviewBrowser->clear();

        if(suffix=="csv"){
            QString lngIn=codec->toUnicode(file->readAll());//暴力读取全部内容

            ui->PreviewBrowser->setText(lngIn);
        }
        else{
            read_lng_to_csv(file,codec);
        }

        file->close();

        isCSVreaded=true;

        return true;
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

           return false;
    }


}

void lng2csv_tool::read_lng_to_csv(QFile *file,QTextCodec *codec)
{
        int index_key=0;
        while(!file->atEnd()){
        //for(int i=0;i<10;i++){
            //QByteArray line=file.readLine();//这是一个偷懒的办法，可以避免从头建立树结构。但是也意味着如果本地化文件不工整读取就会出错
            QString line_string=codec->toUnicode(file->readLine());
            QString key,pre_loc;
            //ui->PreviewBrowser->append(line_string);



            for(int i=0;i<line_string.size();i++){
                QChar now=line_string.at(i);

                if(now==';'){//分号后内容均为注释(因为引号间内容的读取是连续的，所以这里判断为真时读到的引号一定是注释用)
                    //ui->PreviewBrowser->append("检测到注释！");
                    break;
                }
                else if(now=='"'){
                    if(key.isEmpty()){//如果key里没有值，说明即将录入key
                        i++;
                        key.append("\"key_LTMOW_lng");
                        key.append(QString::number(index_key++));//非常暴力，但是可以解决问题！ 即我们发现paratranz只能处理非重复的条目，
                        //但是mow的本地化文件是允许重复key的(因为是树结构，不同结点下的同名key并不一样)，于是我们暴力的给每个条目
                        //都添加一个带索引的前缀，这样所有条目就一定互不相同，然后在读取的时候再删去前缀进行搜索。
                        //而因为建立csv时是自上而下的建立所有key，所以即使删去索引也不必担心恢复成lng时会出错，只要也自上而下的匹配即可
                        //当然这样也有缺点，就是汉化时无法获知该同名条目具体是哪个节点下的，但是key只是索引，
                        //我们可以根据实际内容判定应该如何汉化。而如果要将节点名称加入key，会不可避免地极大增加工作量，也将复杂性从顺序
                        //读取退化到树结构，之前采取的一切简化方法就失效了。
                        key.append("_");
                        while(line_string.at(i)!='"'){
                            if(line_string.at(i)=='\\'){//对转义序列特判，mow似乎支持所有类型的c++转义序列
                                if(line_string.at(i+1)=='"'){
                                    key.append('"');
                                }
                                else{
                                    key.append(line_string.at(i));
                                }//如果不是\"，我们直接读取转义内容。而且转义后行内必然存在额外的结束符，不需要特判
                                i++;
                            }
                            key.append(line_string.at(i));
                            i++;
                        }
                        key.append('"');
                    }
                    else {//那么说明即将录入pre_loc
                        i++;
                        pre_loc.append('"');
                        while(line_string.at(i)!='"'){
                            if(line_string.at(i)=='\\'){//对转义序列特判，mow似乎支持所有类型的c++转义序列
                                if(line_string.at(i+1)=='"'){
                                    pre_loc.append('"');
                                }
                                else{
                                    pre_loc.append(line_string.at(i));
                                }
                                i++;
                            }
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
}

bool lng2csv_tool::read_loc_to_csv(QFile* file,QString suffix)
{
    bool isSuccess=false;
    if(suffix=="csv"){//传递qstringlist似乎很麻烦，不如直接拆成两个函数了
        isSuccess=read_csv_loc(file);
    }
    else{
        isSuccess=read_lng_loc(file);
    }


    return isSuccess;

}

bool lng2csv_tool::read_lng_loc(QFile *file)
{
    QString file_codec=ui->encoding->currentText();

    QTextCodec *codec = QTextCodec::codecForName(file_codec.toUtf8());

    QStringList txtList = ui->PreviewBrowser->toPlainText().split("\n");//未翻译csv

//    for(int i=0;i<txtList.size();i++)
//    qDebug()<<txtList[i]<<endl;

    QString curKey;

    if(file->open(QIODevice::ReadOnly)){

        ui->PreviewBrowser->clear();//删除原内容

        QString lngIn=codec->toUnicode(file->readAll());//暴力读取全部内容

        for(int i=0;i<txtList.size();i++){

            int j=5+9;//跳过一定存在的前缀
            while(txtList[i][j]!='_'){
                ++j;//跳过索引号
            }
            ++j;

            while(txtList[i][j]!='"'){//key一定不存在转义序列(大概) 不能用于非规范的csv文件
                curKey+=txtList[i][j++];
            }

            if(lngIn.indexOf(curKey)!=-1){
                int keyloc=lngIn.indexOf(curKey)+curKey.size()+1;

                int k=keyloc;

                for(;lngIn[k]!='"';k++){}
                ++k;

                if(txtList[i][txtList[i].size()-1]!=','){//说明当前已经填充了翻译，删除它

                    int index=txtList[i].size();

                    int index_i=1;

                    for(int count=0;;index_i++){
                        if(txtList[i][index_i]=='"'){
                            if(txtList[i][index_i+1]=='"'){
                                index_i++;
                            }
                            else if(count!=3){
                                count++;
                            }
                            else{
                                break;
                            }
                        }

                    }

                    //index_i++;//不能直接以逗号为分割，必须手动查

                    txtList[i].remove(index_i,index-index_i);
                }

                txtList[i].append('"');

                while(lngIn[k]!='"'){
                    if(lngIn[k]=='\\'){//对转义序列特判，mow似乎支持所有类型的c++转义序列
                        if(lngIn[k+1]=='"'){
                            txtList[i].append('"');
                        }
                        else{
                            txtList[i].append(lngIn[k]);
                        }
                        k++;
                    }
                    txtList[i].append(lngIn.at(k));
                    k++;
                }

                txtList[i].append('"');

                lngIn.remove(0,k);//因为会存在重复key，而csv文件是严格的自上而下读取，于是只要我们删除已经读取的内容，就可以避免重复读取
            }


            ui->PreviewBrowser->append(txtList[i]);

            curKey.clear();
        }

        file->close();

        return true;
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

        return false;
    }
}

bool lng2csv_tool::read_csv_loc(QFile *file)
{

    QString file_codec=ui->encoding->currentText();

    QTextCodec *codec = QTextCodec::codecForName(file_codec.toUtf8());

    QStringList txtList = ui->PreviewBrowser->toPlainText().split("\n");//未翻译csv

//    for(int i=0;i<txtList.size();i++)
//    qDebug()<<txtList[i]<<endl;

    QString curKey;

    if(file->open(QIODevice::ReadOnly)){

        ui->PreviewBrowser->clear();//删除原内容

        QString lngIn=codec->toUnicode(file->readAll());//暴力读取全部内容

        for(int i=0;i<txtList.size();i++){

            int j=0;//j用于记录当前行要搜索的词条

            if(txtList[i][j]=='"')++j;
            if(txtList[i].mid(1,4)=="key_")j+=4;
            if(txtList[i].mid(5,9)=="LTMOW_lng"){
                j+=9;
                while(txtList[i][j]!='_')++j;
                ++j;

            }//将j移动到实际key的开头

            while(1){
                if(txtList[i][j]=='"'){//对转义序列特判，mow似乎支持所有类型的c++转义序列
                    if(txtList[i][j+1]=='"'){
                        curKey+=txtList[i][j++];
                    }
                    else{
                        break;
                    }
                }
                curKey+=txtList[i][j++];
            }//获取key


            if(lngIn.indexOf(curKey)!=-1){

                int keyloc=lngIn.indexOf(curKey);
                int prefix=0;

                //验证找到的是key而不是别的东西
                while(keyloc!=0&&lngIn[keyloc]!='\n'){//获取在搜索到的key前有多长的前缀与前缀开始的位置
                    keyloc--;
                    prefix++;
                }

                    keyloc++;
                    prefix--;
                    if(lngIn.mid(keyloc,4)=="key_")prefix-=4;
                    if(lngIn.mid(keyloc+4,9)=="LTMOW_lng"){
                        prefix-=9;
                        keyloc+=13;
                        while(lngIn[keyloc]!='_'){
                            ++keyloc;
                            --prefix;
                        }
                        --prefix;
                    }

                if(lngIn[lngIn.indexOf(curKey)+curKey.size()]!=',')prefix=-1;


                if(prefix==0){//确实是要找的key，再开始操作
                    keyloc=lngIn.indexOf(curKey)+curKey.size()+1;

                    if(lngIn[keyloc]=='"'){
                        keyloc++;
                        while(1){
                            if(lngIn[keyloc]=='"'){
                                if(keyloc+1!=lngIn.size()&&lngIn[keyloc+1]=='"'){
                                    ++keyloc;
                                }
                                else{
                                    ++keyloc;
                                    break;
                                }
                            }
                            ++keyloc;
                        }
                    }
                    else{
                        while(keyloc!=lngIn.size()&&lngIn[keyloc]!='\n'&&lngIn[keyloc]!=','){
                            ++keyloc;
                        }
                    }//把keyloc推进到目标翻译位置

                    int k=keyloc;



                    if(k!=lngIn.size()&&lngIn[k]!='\n'){
                        if(lngIn[k+1]=='"'){//有引号，一定可以++
                            ++k;
                        }
                        //if(k+1!=lngIn.size()&&lngIn[k+1]!='\n'){
                            //k+=2;
                            ++k;

                        if(txtList[i][txtList[i].size()-1]!=','){//说明当前已经填充了翻译，删除它

                            int index=txtList[i].size();

                            int index_i=1;

                            for(int count=0;;index_i++){
                                if(txtList[i][index_i]=='"'){
                                    if(txtList[i][index_i+1]=='"'){
                                        index_i++;
                                    }
                                    else if(count!=3){
                                        count++;
                                    }
                                    else{
                                        break;
                                    }
                                }

                            }

                            //index_i++;//不能直接以逗号为分割，必须手动查

                            txtList[i].remove(index_i,index-index_i);
                        }

                        txtList[i].append('"');

                            while(k!=lngIn.size()&&lngIn[k]!='\n'){
                                if(lngIn[k]=='"'){
                                    if(k+1!=lngIn.size()&&lngIn[k+1]=='"'){
                                        txtList[i].append(lngIn.at(k));
                                        k++;
                                    }
                                    else{
                                        break;
                                    }
                                }
                                txtList[i].append(lngIn.at(k));
                                k++;
                            }

                            txtList[i].append('"');



                        //}

                    }


                    lngIn.remove(0,(k==lngIn.size()?k-1:k));//因为会存在重复key，而csv文件是严格的自上而下读取，于是只要我们删除已经读取的内容，就可以避免重复读取



                }


            }


            ui->PreviewBrowser->append(txtList[i]);

            curKey.clear();
        }

        file->close();

        return true;
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

        return false;
    }
}

bool lng2csv_tool::read_loc_to_lng(QFile* file)//还没写
{
    return true;
}

bool lng2csv_tool::checklegal(QString file_in,int readMode)//检查文件合法性
{
    bool isForceRead=ui->checkBox_forceRead->isChecked();

    if(!isForceRead){
        QString suffix=QFileInfo(file_in).suffix();

        if(readMode==0){

            return true;//不需要检查，两种格式都能读
        }
        else if(readMode==1){
            if(!isCSVreaded){//必须先导入原文
                QMessageBox *msgBox;
                    msgBox = new QMessageBox("警告",
                        "尚未导入原文，无法导入翻译！",
                        QMessageBox::Critical,
                        QMessageBox::Ok | QMessageBox::Default,
                        QMessageBox::Cancel | QMessageBox::Escape,
                        0);

                    msgBox->show();

                return false;
            }
            else{
                return true;
            }
        }
        else{
            if(suffix=="csv"){
                QMessageBox *msgBox;
                    msgBox = new QMessageBox("警告",
                        "该功能暂时未完成！",
                        QMessageBox::Critical,
                        QMessageBox::Ok | QMessageBox::Default,
                        QMessageBox::Cancel | QMessageBox::Escape,
                        0);

                    msgBox->show();

                return false;
                //return true;
            }
            else{
                QMessageBox *msgBox;
                    msgBox = new QMessageBox("警告",
                        "文件格式不正确，应为csv格式！",
                        QMessageBox::Critical,
                        QMessageBox::Ok | QMessageBox::Default,
                        QMessageBox::Cancel | QMessageBox::Escape,
                        0);

                    msgBox->show();

                return false;
            }
        }
    }
    else{
        return true;
    }
}

//D:/steam/steamapps/common/Men of War Assault Squad 2/mods/wzss-eastern_asia_pack_v0_7_5/localization/test.lng
