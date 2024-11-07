/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsxfbutton.h
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#ifndef LDLSXFBUTTON_H
#define LDLSXFBUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QMovie>

class LdlsxfButton : public QLabel
{
    Q_OBJECT
public:
    explicit LdlsxfButton(QWidget *parent = nullptr);
public:
    int w = 50,h = 50;//设置按钮大小
    int x,y;//获取按下位置
    int qlablex,qlabley;//获取按键位置
public:
    void setmovie(QMovie *movie);
public:
    virtual void mousePressEvent(QMouseEvent *ev)override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void mousePresssig();
    void mouseReleasesig();

};

#endif // LDLSXFBUTTON_H
