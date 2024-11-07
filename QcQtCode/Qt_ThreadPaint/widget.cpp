#include "widget.h"
#include "qpainter.h"
#include "ui_widget.h"
#include <QThread>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //自定义类对象,需要分配空间,不可以指定父对象
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);

    //把自定义模块添加到子线程
    myT->moveToThread(thread);

    //启动子线程,但是并没有启动线程处理函数
    thread->start();

    connect(ui->pushButton,&QPushButton::clicked,myT,&MyThread::drawImage);
    connect(myT,&MyThread::updateImage,this,&Widget::getimage);

    connect(this,&Widget::destroyed,this,&Widget::dealClose);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(50,50,image);
}
void Widget::getimage(QImage image){
    this->image = image;
    update();   //更新窗口,调用paintevent
}

void Widget::dealClose(){
    thread->quit();
    thread->wait();
    delete myT;
}
