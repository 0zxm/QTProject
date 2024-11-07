/******************************************************************
* @projectName   myTcpserver
* @brief         mainwindow.h
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public:
    QMovie *movie = new QMovie(":/GIF/xhz.gif");
public slots:
    void mousePressslot();
    void mouseReleaseslot();
    void getmvz(int);
    void getRel(int);

};
#endif // MAINWINDOW_H
