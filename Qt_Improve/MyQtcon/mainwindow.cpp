/******************************************************************
* @projectName   myTcpserver
* @brief         mainwindow.cpp
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ldlsxfbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* 自制悬浮窗 */
    ui->ldlsxfbutton->w = 100;
    ui->ldlsxfbutton->h = 100;
    ui->ldlsxfbutton->setGeometry(100,100,ui->ldlsxfbutton->w,ui->ldlsxfbutton->h);
    ui->ldlsxfbutton->setmovie(movie);
    connect(movie, &QMovie::frameChanged,this,&MainWindow::getRel);
    connect(ui->ldlsxfbutton,&LdlsxfButton::mousePresssig,this,&MainWindow::mousePressslot);
    connect(ui->ldlsxfbutton,&LdlsxfButton::mouseReleasesig,this,&MainWindow::mouseReleaseslot);
    /* 自制遥感 */
    ui->ldlsrlButton->setGeometryofrl(100,300,300);
}
void MainWindow::getRel(int frame)//在第一帧停一下
{
    if (frame == 0) {
        // 动画播放到最后一帧时停止
        movie->stop();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
/* 自制悬浮窗 */
void MainWindow::getmvz(int frame)
{
    if (frame == movie->frameCount() - 1) {
        // 动画播放到最后一帧时停止
        movie->stop();
    }
}
void MainWindow::mousePressslot()
{
    disconnect(movie, &QMovie::frameChanged,this,&MainWindow::getRel);
    connect(movie, &QMovie::frameChanged,this,&MainWindow::getmvz);
    movie->start();
    qDebug()<<"悬浮窗按下";
}
void MainWindow::mouseReleaseslot()
{
    disconnect(movie, &QMovie::frameChanged,this,&MainWindow::getmvz);
    connect(movie, &QMovie::frameChanged,this,&MainWindow::getRel);
    movie->start();
    qDebug()<<"悬浮窗松开";
}
