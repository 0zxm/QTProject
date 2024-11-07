/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsrlwidget.h
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#ifndef LDLSRLWIDGET_H
#define LDLSRLWIDGET_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ldlsrlwidget;
}

class ldlsrlwidget : public QWidget
{
    Q_OBJECT

public:
    explicit ldlsrlwidget(QWidget *parent = nullptr);
    ~ldlsrlwidget();

private:
    Ui::ldlsrlwidget *ui;
public slots:
    void getXYsig(int Xsig,int Ysig);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
signals:
    void set1sig(int);
    void set2sig(int);
    void set3sig(int);
};

#endif // LDLSRLWIDGET_H
