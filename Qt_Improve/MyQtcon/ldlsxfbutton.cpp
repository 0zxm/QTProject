/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsxfbutton.cpp
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#include "ldlsxfbutton.h"

LdlsxfButton::LdlsxfButton(QWidget *parent) : QLabel(parent)
{
}
void LdlsxfButton::setmovie(QMovie *movie)
{
    setMovie(movie);
    movie->start();
}
void LdlsxfButton::mousePressEvent(QMouseEvent *ev)//重写鼠标点击事件,发送信号
{
    if(ev->button() == Qt::LeftButton){
//            QString str = QString("鼠标按下了 x=%1   y=%2   globalX = %3   globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
//            qDebug() << str;
        x = ev->globalX();
        y = ev->globalY();
        qlablex = pos().x();
        qlabley = pos().y();
        emit mousePresssig();
    }
}
void LdlsxfButton::mouseMoveEvent(QMouseEvent *ev)//重写鼠标移动事件,形成悬浮窗
{
    setGeometry(qlablex+ev->globalX()-x,qlabley+ev->globalY()-y,w,h);
}
void LdlsxfButton::mouseReleaseEvent(QMouseEvent *ev)//重写鼠标松开事件,发送信号
{
    if(ev->button() == Qt::LeftButton){
        emit mouseReleasesig();
    }
}
