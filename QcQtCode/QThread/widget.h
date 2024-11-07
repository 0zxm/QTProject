#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>   //定时器头文件
#include <QThread>
#include "mythread.h"
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

    void dealTimeout(); //处理定时器槽函数

    void dealDone();    //处理线程槽函数

    void stopThread();  //关闭窗口时停止线程槽函数
private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QTimer * myTimer;

    MyThread * thread;  //线程对象


};
#endif // WIDGET_H
