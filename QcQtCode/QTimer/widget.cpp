#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);

    connect(myTimer,&QTimer::timeout,[=](){
        static int i = 0;
        i++;
        ui->lcdNumber->display(i / 10.0);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_start_clicked()
{
    //启动定时器
    //时间间隔为100毫秒,每次间隔触发timeout()信号
    if(!myTimer->isActive()){
        myTimer->start(100);
    }


}


void Widget::on_pushButton_stop_clicked()
{
    if(myTimer->isActive())
        myTimer->stop();
}


void Widget::on_pushButton_clear_clicked()
{
    ui->lcdNumber->display("0.0");
    ui->pushButton_stop->click();
}

