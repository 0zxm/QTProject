/******************************************************************
* @projectName   myTcpserver
* @brief         main.cpp
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
