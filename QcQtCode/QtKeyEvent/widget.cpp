#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    label->setFixedSize(50,50);
    label->setStyleSheet("QLabel{background-color:rgb(0,0,0);}");
    label->move(0,0);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent * keyevent){
    int curX = label->pos().x();
    int curY = label->pos().y();

    int curWidth = this->width();
    int curHeight = this->height();

    // int num = 0;
    if(keyevent->key() == Qt::Key_Up){
        if(curY > 50){
            label->move(curX,curY-50);
        }else label->move(curX,curY+curHeight-50);/*num++;*/
    }else if(keyevent->key() == Qt::Key_Down){
        if(curY < curHeight - 50){
            label->move(curX,curY+50);
        }else label->move(curX,curY-curHeight+50);/*num++;*/
    }else if(keyevent->key() == Qt::Key_Left){
        if(curX > 50){
            label->move(curX-50,curY);
        }else label->move(curX+curWidth-50,curY); /*num++;*/
    }else if(keyevent->key() == Qt::Key_Right){
        if(curX < curWidth - 50){
            label->move(curX+50,curY);
        }else label->move(curX-curWidth+50,curY);/*num++;*/
    }

    // if(num == 1){
    //     label->move(0,0);
    //     num--;
    // }
}
