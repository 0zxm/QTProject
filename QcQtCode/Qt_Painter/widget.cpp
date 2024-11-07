#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    Posx = 10;
    Posy = 10;
    //设置按钮点击事件
    connect(ui->pushButton, &QPushButton::clicked,[=](){
        Posx += 10;
        Posy += 10;
        //update会自动调用paintEvent函数
        update();
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *){
    //实例化画家对象
    QPainter painter(this);//这个this指定的是绘图的设备,当前窗口

    if(Posx >= this->width()){
        Posx = 10;
    }

    if(Posy >= this->height()){
        Posy = 10;
    }

    //用画家对象画图
    painter.drawPixmap(Posx,Posy,QPixmap(":/Image/OnePiece.png"));

    // painter.drawEllipse(QPoint(100,100),50,50);

    // //设置抗锯齿  效率低
    // painter.setRenderHint(QPainter::Antialiasing);

    // painter.drawEllipse(QPoint(250,100),50,50);

    // painter.drawRect(QRect(20,20,50,50));

    // painter.translate(QPoint(100,0));//移动画家

    // painter.save();//保存画家状态

    // painter.drawRect(QRect(20,20,50,50));

    // painter.translate(QPoint(100,0));//移动画家

    // painter.restore();//取消画家状态

    // painter.drawRect(QRect(20,20,50,50));

    // //设置画笔
    // QPen pen(QColor(255,0,0));
    // pen.setWidth(3);//设置画笔宽度
    // //设置画笔风格
    // pen.setStyle(Qt::DotLine);
    // //让画家使用这支笔
    // painter.setPen(pen);

    // //设置笔刷
    // QBrush brush(Qt::cyan);
    // //设置画刷风格
    // brush.setStyle(Qt::Dense7Pattern);
    // //让画家使用画刷
    // painter.setBrush(brush);




    // //画线
    // painter.drawLine(QPoint(0,0), QPoint (100, 100));

    // //画圆
    // painter.drawEllipse(QPoint(100,100),50,50);

    // //画矩型
    // painter.drawRect(QRect(20,20,50,50));

    // //画文字
    // painter.drawText(QRect(100,100,200,200),"好好学习天天向上");


}
