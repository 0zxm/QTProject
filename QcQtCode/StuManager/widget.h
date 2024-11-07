#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QTableWidget>
#include <QDebug>
#include <QTextStream>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QAbstractItemView>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //从指定的文件读取数据
    void readDataFromFile(const QString& filename);
    //保存到指定文件
    void saveDataToFile(const QString& filename);

    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::Widget *ui;
    bool isSave = true;//文件是否保存
    int currentColumn = 0;

};
#endif // WIDGET_H
