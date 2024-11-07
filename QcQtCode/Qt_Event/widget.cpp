#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器1
    id1 = startTimer(1000);//参数1 间隔(毫秒单位)
    //定时器2
    id2 = startTimer(2000);//返回值是此定时器id

    //第二种定时器
    QTimer * timer = new QTimer(this);
    //启动定时器
    timer->start(500);
    connect(timer, &QTimer :: timeout, timer, [=](){
        static int x = 0;
        ui->label_4->setText(QString :: number(x++));
    });

}
void Widget :: timerEvent(QTimerEvent *e){//参数e有两个对外接口,e->timerId()返回定时器id
    //label1
    if(e->timerId() == id1){
        static int num = 1;
        ui->label_2->setText(QString ::  number(num++));
    }

    //label2每隔两秒+1
    if(e->timerId() == id2){
        static int num2 = 1;
        ui->label_3->setText(QString ::  number(num2++));
    }
    //给label安装事件过滤器
    //1.安装过滤器
    ui->label->installEventFilter(this);//父类,谁给控件安装过滤器
}
//2.重写eventfilter事件

bool  Widget :: eventFilter(QObject * obj, QEvent * e){
    if(obj ==ui->label){
        if(e->type() == QEvent :: MouseButtonPress){
            QMouseEvent * ev = static_cast<QMouseEvent *> (e);//静态类型转换
            QString str = QString("事件过滤器----鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalX()).arg(ev->globalY());
            qDebug()<<str;

            return true;//表示自己处理,不向下分发
        }
    }
    //其他默认处理
    return QWidget :: eventFilter(obj,e);
}

Widget::~Widget()
{
    delete ui;
}
