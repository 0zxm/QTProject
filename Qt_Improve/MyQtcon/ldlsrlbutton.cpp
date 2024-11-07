/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsrlbutton.cpp
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#include "ldlsrlbutton.h"

LdlsrlButton::LdlsrlButton(QWidget *parent) : QLabel(parent)
{
    widget = new ldlsrlwidget();
    connect(this,&LdlsrlButton::toXYsig,widget,&ldlsrlwidget::getXYsig);
    connect(widget,&ldlsrlwidget::set1sig,this,&LdlsrlButton::get1sig);
    connect(widget,&ldlsrlwidget::set2sig,this,&LdlsrlButton::get2sig);
    connect(widget,&ldlsrlwidget::set3sig,this,&LdlsrlButton::get3sig);
}
void LdlsrlButton::setGeometryofrl(int r,int x,int y)//设置遥杆位置及大小
{
    radius = r;
    R = radius/2;
    rlX = radius+R*2;
    rlY = radius+R*2;
    setGeometry(x,y,(radius+R*2)*2,(radius+R*2)*2);
    repaint();
}
int LdlsrlButton::getra(int xory)//基于摇杆分辨率获得偏差值
{
    if(dirlfl == true){
        xory = xory-radius-R*2;
        xory = xory*ra/radius;
        return xory;
    }
    else return 0;
}
/* 事件重写 */
void LdlsrlButton::mousePressEvent(QMouseEvent *ev)//重写鼠标点击事件
{
    if(ev->button() == Qt::LeftButton){
        qDebug() << "鼠标左键按下";
    }
    else if(ev->button() == Qt::RightButton){
        qDebug() << "鼠标右键按下";

        widget->setAttribute(Qt::WA_DeleteOnClose,true);
        widget->setWindowModality(Qt::NonModal);
        widget->setWindowTitle(tr("遥感调试窗口"));
        widget->show();
    }
}
void LdlsrlButton::mouseMoveEvent(QMouseEvent *ev)//重写鼠标移动事件
{
    rlX = ev->x();
    rlY = ev->y();
    int L = radius;//限位半径
    int rlL2 =(rlX-radius-R*2)*(rlX-radius-R*2)+(rlY-radius-R*2)*(rlY-radius-R*2);//遥杆偏离半径的平方
    if(rlL2 >= L*L){
        rltfl = true;
        dirlfl = true;
        rlX =(L/sqrt(rlL2))*(rlX-radius-R*2)+radius+R*2;
        rlY =(L/sqrt(rlL2))*(rlY-radius-R*2)+radius+R*2;
        emit toXYsig(getra(rlX),getra(rlY));
        repaint();
    }
    else{
        rltfl = false;
        emit toXYsig(getra(rlX),getra(rlY));
        repaint();
        if(sqrt(rlL2)*100/L>dirl){
            dirlfl = true;
        }
        else dirlfl = false;
    }
}
void LdlsrlButton::mouseReleaseEvent(QMouseEvent *ev)//重写鼠标松开事件
{
    if(ev->button() == Qt::LeftButton){
        rltfl = false;
        rlX = radius+R*2;
        rlY = radius+R*2;
        emit toXYsig(getra(rlX),getra(rlY));
        repaint();
    }
}
void LdlsrlButton::paintEvent(QPaintEvent *event){//重写绘图事件
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);  // 使用抗锯齿效果
    //绘制限位
    if(rltfl == false){
        pen.setColor(QColor(200,200,200));
    }
    else{
        pen.setColor(QColor(0,255,255));
    }
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawEllipse(R*2, R*2, radius*2, radius*2);
    //绘制死区
    pen.setColor(QColor(150,150,150));
    painter.setBrush(QColor(150,150,150));
    painter.setPen(pen);
    painter.drawEllipse(R*2+3, R*2+3, radius*2-6, radius*2-6);
    pen.setColor(QColor(230,230,230));
    painter.setBrush(QColor(230,230,230));
    painter.setPen(pen);
    painter.drawEllipse(R*2+3+((radius-3)*(100-dirl))/100,R*2+3+((radius-3)*(100-dirl))/100,
                        (radius*2-6)*dirl/100,(radius*2-6)*dirl/100);
    //绘制遥感帽
    pen.setColor(QColor(200,255,255));
    painter.setBrush(QColor(0,255,255));
    painter.setPen(pen);
    painter.drawEllipse(rlX-R, rlY-R, R*2, R*2);
}
/* 遥感接受参数设置 */
void LdlsrlButton::get1sig(int set)
{
    setGeometryofrl(set,300,300);
}
void LdlsrlButton::get2sig(int set)
{
    dirl = set;
    repaint();
}
void LdlsrlButton::get3sig(int set)
{
    ra = set;
}
