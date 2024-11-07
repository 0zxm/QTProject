#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);//系统提供的构造函数

    //MyPushButton();
    ~MyPushButton();
signals:
};

#endif // MYPUSHBUTTON_H
