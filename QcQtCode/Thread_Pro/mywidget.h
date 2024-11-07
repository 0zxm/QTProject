#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void dealSignal();
private slots:
    void on_pushButton_start_clicked();
    //启动子线程的信号
    void on_pushButton_stop_clicked();

    void dealDestoryed();

signals:
    void startThread();
private:
    Ui::MyWidget *ui;

    MyThread * myT;
    QThread * thread;
};
#endif // MYWIDGET_H
