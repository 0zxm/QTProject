#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    //只要定时器启动,自动触发timeout信号
    connect(myTimer,&QTimer::timeout,this,&Widget::dealTimeout);

    //分配空间
    thread = new MyThread(this);

    connect(thread,&MyThread::isDone,this,&Widget::dealDone);

    //当点击右上角×时,触发信号
    connect(this,&Widget::destroyed,this,&Widget::stopThread);
}

Widget::~Widget()
{
    delete ui;
}
void Widget :: dealTimeout(){

    //处理定时器槽函数
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);

}
void Widget::on_pushButton_clicked()
{
    if(myTimer->isActive() == false){
        myTimer->start(100);    //100ms
    }

    //启动线程处理数据

    thread->start();
    // //模拟处理复杂数据
    // QThread::sleep(5);

    // // myTimer->stop();
    // qDebug() << "stop";
}

void Widget::dealDone(){
    myTimer->stop();
    qDebug() << "is over";
}
void Widget::stopThread(){
    //关闭线程函数,不一定马上生效
    thread->quit();
    //等待线程处理完手头工作
    thread->wait();
}
