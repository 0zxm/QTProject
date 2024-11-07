#include "mylabel.h"

myLabel::myLabel(QWidget *parent)
    : QLabel{parent}
{
    this->setMouseTracking(true);//设置鼠标追踪
}
// //鼠标进入
// void myLabel::enterEvent(QEnterEvent *event){
//     qDebug()<<"鼠标进入";
// }
// //鼠标离开事件
// void myLabel::leaveEvent(QEvent *event){
//     qDebug()<<"鼠标离开";
// }
//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *ev){
    //if鼠标左键,提示信息
    if(ev->button() == Qt::LeftButton){
        QString str = QString("鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    }

}
//鼠标释放
void myLabel::mouseReleaseEvent(QMouseEvent *ev){
    QString str = QString("鼠标释放了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
    qDebug()<<str;
}
//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *ev){
    // if(ev->buttons() & Qt::LeftButton){//必须是鼠标左键从头到尾移动才为真
        QString str = QString("鼠标移动了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    // }
}
bool myLabel:: event(QEvent * e){
    if(e->type() == QEvent :: MouseButtonPress)
    {
        QMouseEvent * ev = static_cast<QMouseEvent *> (e);//静态类型转换
        QString str = QString("event鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug()<<str;
    }
}
