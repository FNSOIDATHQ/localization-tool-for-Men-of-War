#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QPushButton>

#include "mainwindow.h"
#include "lng2csv_tool.h"

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();

    QPushButton *done,*exit;

    MainWindow *mainw;

    lng2csv_tool *switchTool;

private:
    Ui::SelectDialog *ui;

public slots:
    void selectTools();
};

#endif // SELECTDIALOG_H
