#include "widget.h"
#include "ui_widget.h"
#include <QPoint>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);//去掉窗口标题

    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent * paintevent){
    QPainter painter(this);

    painter.drawPixmap(0,0,width(),height(),QPixmap(":/R-C.jfif"));
}

// void Widget::on_pushButton_clicked()
// {
//     this->close();
// }

//鼠标按下
void Widget::mousePressEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton)
        mousepress = true;
    //窗口移动的距离
    movepoint = ev->globalPosition().toPoint() - pos();
}
//鼠标释放
void Widget::mouseReleaseEvent(QMouseEvent *ev){
    Q_UNUSED(ev);
    mousepress = false;
}
//鼠标移动
void Widget::mouseMoveEvent(QMouseEvent *ev) {
    if(mousepress){
        //窗口的初始位置
        QPoint movePos = ev->globalPosition().toPoint();
        move(movePos - movepoint);
    }
}

