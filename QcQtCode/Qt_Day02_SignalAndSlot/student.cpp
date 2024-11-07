#include "student.h"
#include <QDebug>
Student::Student(QObject *parent)
    : QObject{parent}
{}
void Student :: treat(){
    qDebug() << "请老师吃个饭";
}
void Student :: treat(QString foodname){
    //QString转成char*,先转成QByteArray(toUtf8()),再转char*(data())

    qDebug() << "请老师吃"<< foodname.toUtf8().data();
    //打印char*不加引号,打印QString加引号//请老师吃 "宫保鸡丁"
}
