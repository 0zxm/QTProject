#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击按钮,获取控件值
    connect(ui->btn_get, &QPushButton::clicked,[=](){
        qDebug() << ui->widget->getNumber();
    });

    //设置到一半
    connect(ui->btn_set, &QPushButton::clicked,[=](){
        ui->widget->setNumber(50);
    });
}

Widget::~Widget()
{
    delete ui;
}
