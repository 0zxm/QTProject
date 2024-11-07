#ifndef STUDENTDLG_H
#define STUDENTDLG_H

#include <QDialog>


#include <QSqlDatabase> // 专用于连接、创建数据库
#include <QSqlQuery> // 专用于DML（数据操纵语言）、DDL（数据定义语言）
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSortFilterProxyModel>


QT_BEGIN_NAMESPACE
namespace Ui { class StudentDlg; }
QT_END_NAMESPACE

class StudentDlg : public QDialog
{
    Q_OBJECT

public:
    StudentDlg(QWidget *parent = nullptr);
    ~StudentDlg();

private slots:
    void on_pushButtonSort_clicked();

    void on_pushButton_INSERT_clicked();

    void on_pushButton_DELETE_clicked();

    void on_pushButton_UPDATE_clicked();

    void on_pushButton_SEARCH_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:  // 自定义函数
    void CreateDatabaseFunc();  // 创建SQLite数据库
    void CreateTableFunc();     // 创建SQLite数据表
    void QueryTableFunc();      // 执行查询操作

    QSqlDatabase sqldb;         // 创建Qt和数据库链接
    QSqlQueryModel sqlmodel;    // 存储结果集
    QModelIndex currentIndexModel;//当前点击行
    QSqlQuery testquery; //在此例中设置全局指针变量会崩溃,不知道为什么,要创建函数局部变量,可能是创建表时和初始化时用的都是局部变量,结果存在里面被销毁了
    int scence = 1; //第几个场景
private:
    Ui::StudentDlg *ui;

















};
#endif // STUDENTDLG_H
