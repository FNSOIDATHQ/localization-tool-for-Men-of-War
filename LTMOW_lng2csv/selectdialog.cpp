#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);

    setWindowTitle("选择器");

    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);

    done=new QPushButton();
    exit=new QPushButton();

    done->setText("确定");
    //done->setDefault(true);
    exit->setText("退出");


    ui->buttonBox->addButton(done,QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(exit,QDialogButtonBox::RejectRole);
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::selectTools()
{
    int type=ui->comboBox->currentIndex();

    if(type==0){//0=文件转换工具 1=本地化文件生成工具
        switchTool=new lng2csv_tool();
        switchTool->show();
    }
    else{
        mainw=new MainWindow();
        mainw->show();
    }

    this->close();
}
