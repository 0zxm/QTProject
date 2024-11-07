/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsrlbutton.h
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#ifndef LDLSRLBUTTON_H
#define LDLSRLBUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include "ldlsrlwidget.h"

class LdlsrlButton : public QLabel
{
    Q_OBJECT
public:
    explicit LdlsrlButton(QWidget *parent = nullptr);
public:
    ldlsrlwidget *widget;
    void setGeometryofrl(int r,int x,int y);
public:
    virtual void mousePressEvent(QMouseEvent *ev)override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void paintEvent(QPaintEvent *event) override;
private:
    bool rltfl = false;//摇杆超出界限标志
    bool dirlfl = false;//摇杆超出死区标志位
    /* 遥杆帽 */
    int R = 20;
    int rlX;//
    int rlY;
    /* 遥杆限位 */
    int radius = 100;//半径
    /* 遥杆死区 */
    int dirl = 0;
    /* 遥杆灵敏度 */
    int ra = 1000;
private:
    int getra(int);
public slots:
    void get1sig(int);
    void get2sig(int);
    void get3sig(int);
signals:
    void toXYsig(int Xsig,int Ysig);
};

#endif // LDLSRLBUTTON_H
