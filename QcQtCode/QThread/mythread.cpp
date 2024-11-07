#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{}
void MyThread::run(){
    //模拟数据处理
    QThread::sleep(5);
    emit this->isDone();
}
