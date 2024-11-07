#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow> //包含QWeight类

class MainWindow : public QMainWindow
{
    Q_OBJECT//宏,允许程序使用信号和槽机制

public:
    MainWindow(QWidget *parent = nullptr);//构造
    ~MainWindow();//析构函数
};
#endif // MAINWINDOW_H
