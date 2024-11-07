#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QSqlDatabase>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//没找到QMySql
    QStringList driver_list= QSqlDatabase::drivers(); //获取支持的驱动名
    qDebug() << driver_list; // QList("QSQLITE", "QODBC", "QPSQL")

    //设置连接属性
    db.setHostName("localhost"); //127.0.0.1或者本机ip地址
    db.setUserName("root");
    db.setDatabaseName("mysql");
    db.setPassword("Xubin159753123");
    db.setPort(3306);


    if(!db.open()){
        qDebug() << "失败原因" << db.lastError().text();
        return;
    }else{
        qDebug() << "连接成功";
    }
    QSqlQuery query;
    QString sql_cmd = "select * from students";
    query.exec(sql_cmd); // 如果执行成功,query对象会存储结果集
    while(query.next()){
        //取出当前记录的字段
        qDebug() << query.value(0).toInt()
                 << query.value(0).toInt()
                 << query.value("student_class").toString();
    }
    QString cmd = "CREATE TABLE teachers (id INT AUTO_INCREMENT PRIMARY KEY,  name VARCHAR(255) NOT NULL  );";
    query.exec(cmd);
    db.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
