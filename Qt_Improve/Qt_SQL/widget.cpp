#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");指定连接数据库的驱动名
    // db.setHostName("127.0.0.1");
    // db.setPort(3306);
    // db.setDatabaseName("是你在ODBC中创建的Data　source name");
    // db.setUserName("用户名");
    // db.setPassword("密码");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("Xubin159753123");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "success");
    }
    else {
        QMessageBox::information(this, "infor", "open failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
    // 3.qt通过ODBC操作数据库
    // 1)查询数据
    //查询数据库中所有表的名称
    QStringList tables = db.tables();
    foreach(QString table, tables)
        qDebug()<<table;

    //ODBC查询数据
    QSqlQuery result = db.exec(" select * from users");
    while(result.next()){
        qDebug()<<"user_id:"<<result.value("user_id").toInt();
        qDebug()<<"name:"<<result.value("name").toString();
        qDebug()<<"password:"<<result.value("password").toString();
        qDebug()<<"score:"<<result.value("score").toInt()<<Qt::endl;
    }

    //ODBC插入数据
    result.clear();
    bool result_successed = result.exec("insert into users(name,password,score) values ( 'joe2y','123456',0)");

    if(result_successed){
        qDebug()<<"插入成功！";
    }else {
        qDebug()<<"插入失败！";
    }

    //ODBC更新数据
    result.clear();
    bool result_successed2 = result.exec("update users set score=10 where user_id=2");

    if(result_successed2){
        qDebug()<<"更新成功！"<<Qt::endl;
    }else{
        qDebug()<<"更新失败！"<<Qt::endl;
    }

}

Widget::~Widget()
{
    delete ui;
}
