#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QMap>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class Setting;
}

struct unit_data{
    bool b_is_modifed;//当前条目是否修改过
    bool b_need_localize;//当前项是否为需要本地化的内容
    int index;//查找时在表内的位置，用于快速在树里定位单位
    QString text;//本地化内容
};

Q_DECLARE_METATYPE(unit_data)

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private:
    Ui::Setting *ui;

    QMap<QString,QString> link_set;

    QString pre_type,pre_link;

public slots:
    void quick_type_local();
    void quick_type_res();
    void quick_type_unit_type();
    void when_button_accepted();
    void change_link_set();


signals:
    void readpath(QString, QString,QMap<QString,QString>);
};

#endif // SETTING_H
