#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>
#include <QImage>
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

    //重写绘图事件
    void paintEvent(QPaintEvent *);
    void getimage(QImage image);

    void dealClose();//窗口关闭槽函数

private:
    Ui::Widget *ui;

    QImage image;
    MyThread * myT;
    QThread * thread;   //子线程

};
#endif // WIDGET_H
