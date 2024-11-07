#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QPicture>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // //Pixmap绘图设备 专门为平台做了显示的优化
    // QPixmap map(300, 300);

    // //填充颜色
    // map.fill(Qt::white);

    // //画家
    // QPainter painter(&map);
    // painter.setPen(QPen(Qt :: green));
    // painter.drawEllipse(QPoint(150, 150), 100, 100);

    // //保存
    // map.save("D:\\map.png");

    // //QImage绘图设备
    // QImage img(300,300,QImage::Format_RGB32);
    // img.fill(Qt::white);
    // QPainter painter(&img);
    // painter.setPen(QPen(Qt :: blue));
    // painter.drawEllipse(QPoint(150, 150), 100, 100);
    // img.save("D:\\img.png");


    //QPicture绘图设备  可以记录和重现绘图指令
    QPicture pic;
    QPainter painter;
    painter.begin(&pic); //往pic上画
    painter.setPen(Qt::cyan);
    painter.drawEllipse(QPoint(150, 150), 100, 100);


    painter.end();//结束画画

    pic.save("D:\\pic.xb");//保存
}

//绘图事件
void Widget :: paintEvent(QPaintEvent *){
    QPainter painter(this);

    // //使用QImage修改像素
    // QImage img;
    // img.load(":/Image/Luffy.png");

    // //修改像素点
    // for(int i = 50; i < 100; i++){
    //     for(int j = 50; j < 100; j++){

    //         QRgb value = qRgb(255, 0 , 0);
    //         img.setPixel(i, j, value);
    //     }
    // }
    // painter.drawImage(0, 0, img);


    //重现绘图指令
    QPicture pic;
    pic.load("D:\\pic.xb");
    painter.drawPicture(0, 0, pic);



}




Widget::~Widget()
{
    delete ui;
}
