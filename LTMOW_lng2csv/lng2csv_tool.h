#ifndef LNG2CSV_TOOL_H
#define LNG2CSV_TOOL_H

#include <QMainWindow>

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
    void quick_type_lng();
    void read_lng_file();
    void save_csv_file();
private:
    Ui::lng2csv_tool *ui;

    QString file_name;
};

#endif // LNG2CSV_TOOL_H
