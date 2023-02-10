#ifndef LNG2CSV_TOOL_H
#define LNG2CSV_TOOL_H

#include <QMainWindow>
#include <QFile>
#include <QPushButton>

namespace Ui {
class lng2csv_tool;
}

class lng2csv_tool : public QMainWindow
{
    Q_OBJECT

public:
    explicit lng2csv_tool(QWidget *parent = nullptr);
    ~lng2csv_tool();

public slots:
    void quick_type_file_path();
    void read_file();
    void save_file();
    void turnto_import_translate_mode(int index);
private:
    Ui::lng2csv_tool *ui;

    QString file_name;
    QString pre_path;

    bool isCSVreaded,isLNGreaded;

    bool read_ori_to_csv(QFile* file,QString suffix);

    void read_lng_to_csv(QFile* file,QTextCodec *codec);

    bool read_loc_to_csv(QFile* file,QString suffix);

    bool read_lng_loc(QFile* file);
    bool read_csv_loc(QFile* file);

    bool read_loc_to_lng(QFile* file,QPushButton* shooter);

    bool checklegal(QString file_in,int readMode,QPushButton* shooter);

    void setOriReadVisiable(bool mode);
};

#endif // LNG2CSV_TOOL_H
