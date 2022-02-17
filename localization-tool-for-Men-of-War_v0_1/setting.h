#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private:
    Ui::Setting *ui;

public slots:
    void quick_type_local();
    void quick_type_res();
    void when_button_accepted();


signals:
    void readpath(QString, QString);
};

#endif // SETTING_H
