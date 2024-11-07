#include "mypushbutton.h"
#include <QDebug>
MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{
    qDebug() << "我的按钮类被调用";
}
MyPushButton :: ~MyPushButton(){
    qDebug() << "我的按钮类被析构";
}
