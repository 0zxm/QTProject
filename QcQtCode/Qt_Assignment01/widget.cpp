#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton * btn = new QPushButton("OPEN", this);
    btn->setFixedSize(200,200);

    connect(btn,&QPushButton :: clicked,this,[=](){
        QWidget * w = new QWidget;
        w->setWindowTitle("第二个窗口");
        //w->show();
        QPushButton * btn2 = new QPushButton("close", w);
        w->show();
        connect(btn2, &QPushButton :: clicked, w, [=](){
            w->close();
        });

    });
}

Widget::~Widget() {}
