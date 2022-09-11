#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


    Ui::MainWindow *ui;

    Setting *setting;



    QString res_path,local_path;

    QFileInfoList breed,stuff,weapon,unit;

    QFileInfoList *cur_type;

    QDir res,local;

    QStandardItemModel *Tree_Data;

    QStandardItem *cur_select;

    QMap<QString,QString> localize_link;

    double pre_precent;
    int pre_value;
    int ori_y;
    int unit_num;

    int read_unit_universal(QDir path,QFileInfoList &tar,QString suffix_Filter);

    int create_tree(QFileInfoList,QString,int);

    void refresh_unit_edit();

    void unit_data_update(bool b_need_localize,int index,QString text);

private slots:
    void getpath(QString, QString,QMap<QString,QString>);
public slots:
    void open_setting();
    void read_unit();
    void change_show_box(QString);
    void scrollbar_move(int);
    void save_cur_unit();
    void show_unit(QModelIndex);
    void save_current_type();
    void change_localize_state();

};
#endif // MAINWINDOW_H
