#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");//使用静态方法
    db.setDatabaseName("manager.db");
    db.open();

    query = new QSqlQuery();
    query->exec("create table userinfo(username,password)");

    qmodel = new QSqlQueryModel();
    qmodel->setQuery("select * from userinfo"); //*可替换成username as 用户名,password as 密码  取别名方式
    ui->tableView->setModel(qmodel);
    //改表头方式
    qmodel->setHeaderData(0,Qt::Horizontal,"账号");
    qmodel->setHeaderData(1,Qt::Horizontal,"密码");
};

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString sql = ("insert into userinfo(username,password) VALUES('"+username+"','"+password+"')" );
    query->exec(sql);
    qmodel->setQuery("select * from userinfo");
    QMessageBox::about(this,"消息","添加成功");


}


void Widget::on_tableView_clicked(const QModelIndex &index)
{
    QString username = index.siblingAtColumn(0).data().toString();//获取一行的第一列里的内容,转成字符串
    QString password = index.siblingAtColumn(1).data().toString();

    ui->lineEdit->setText(username);
    ui->lineEdit_2->setText(password);

    currentIndexModel = index;
}


void Widget::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString sql = ("update userinfo set password ='"+password+"' where username = '"+username+"' " );//update修改信息
    query->exec(sql);
    qmodel->setQuery("select * from userinfo");
    QMessageBox::about(this,"消息","修改成功");
}


void Widget::on_pushButton_3_clicked()
{
    // QString username = ui->lineEdit->text(); //借助lineEdit
    QString username = currentIndexModel.siblingAtColumn(0).data().toString();
    QString sql = ("delete from userinfo where username= '"+username+"'");//update修改信息
    query->exec(sql);
    qmodel->setQuery("select * from userinfo");
    QMessageBox::about(this,"消息","删除成功");
}


void Widget::on_pushButton_4_clicked()
{
    QString username = ui->lineEdit->text();
    if(username!=""){
        QString sql = "SELECT * FROM userinfo WHERE username = '"+username+"';";
        query->exec(sql);
        qmodel->setQuery(sql);
        QPushButton * backBtn = new QPushButton(this);
        backBtn->setText("返回");
        backBtn->setGeometry(0,0,50,20);
        backBtn->show();
        connect(backBtn,&QPushButton::clicked,[=](){
            qmodel->setQuery("select * from userinfo");
            backBtn->hide();
        });

    }

}

