#include "mythread.h"
#include "qdebug.h"
#include <QThread>
MyThread::MyThread(QObject *parent)
    : QObject{parent}
{
    this->isStop = false;
}
void MyThread::myTimeout(){
    while(this->isStop == false)
    {
        QThread::sleep(1);
        emit this->mySignal();
        qDebug() << "子线程号" << QThread::currentThread();

        if(this->isStop == true){
            break;
        }
    }
}
void MyThread::setFlag(bool flag){
    isStop = flag;
}
