#include "mythread.h"
#include <QPoint>
#include <QPainter>
#include <QRandomGenerator>
#include <QPen>
#include <QBrush>
MyThread::MyThread(QObject *parent)
    : QObject{parent}
{}

void MyThread::drawImage(){

    //定义QImage绘图设备
    QImage img(500,500,QImage::Format_ARGB32);
    //定义画家,指定绘图设备
    QPainter p(&img);

    //定义画笔对象
    QPen pen;
    pen.setWidth(5);//设置宽度
    p.setPen(pen);

    //定义画刷
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);   //设置样式
    brush.setColor(Qt::red);
    //把画刷交给画家
    p.setBrush(brush);

    //定义五个点
    QPoint points[] = {
        QPoint(QRandomGenerator::global()->bounded(500),QRandomGenerator::global()->bounded(500)),
        QPoint(QRandomGenerator::global()->bounded(500),QRandomGenerator::global()->bounded(500)),
        QPoint(QRandomGenerator::global()->bounded(500),QRandomGenerator::global()->bounded(500)),
        QPoint(QRandomGenerator::global()->bounded(500),QRandomGenerator::global()->bounded(500)),
        QPoint(QRandomGenerator::global()->bounded(500),QRandomGenerator::global()->bounded(500))
    };

    p.drawPolygon(points, 5);

    //通过信号发送图片
    emit this->updateImage(img);
}
