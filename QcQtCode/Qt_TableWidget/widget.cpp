#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //TableWidget控件

    ui->tableWidget->resize(300,500);

    //设置列数
    ui->tableWidget->setColumnCount(3);

    //设置水平表头
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "性别" << "年龄");//匿名对象

    //设置行数
    ui->tableWidget->setRowCount(5);

    //设置正文
    //ui->tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
    QStringList nameList;
    nameList << "张飞"<<"曹操" << "花木兰" << "关羽" << "刘备";

    QList<QString> sexList;
    sexList << "男" << "男" << "女" << "男"  << "男";
    for(int i = 0; i < 5; i++){
        int col = 0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(nameList[i]));//不会抛出异常
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(nameList.at(i)));//抛出异常
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString :: number(18)));//int转QString
   }

}

Widget::~Widget()
{
    delete ui;
}
