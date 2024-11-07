#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //重置窗口大小
    this->resize(600,400);
    //菜单栏做多只能有一个
    //创建菜单栏
    QMenuBar * bar = menuBar();
    //置在窗口中
    setMenuBar(bar);
    //添加菜单
    QMenu * fileMenu = bar->addMenu("文件");
    QMenu * editMenu = bar->addMenu("编辑");
    //创建菜单项
    QAction * newAction = fileMenu->addAction("新建");
    //添加分隔符
    fileMenu->addSeparator();
    QAction * openAction = fileMenu->addAction("打开");

    //工具栏(可以有多个)tool
    QToolBar * toolbar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea,toolbar);//默认停靠范围

    //后期设置只允许左右停靠
    toolbar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //设置浮动操作
    toolbar->setFloatable(false);

    //设置移动
    toolbar->setMovable(false);

    //工具栏中设置内容
    toolbar->addAction(newAction);
    toolbar->addSeparator();
    toolbar->addAction(openAction);

    //工具栏中添加控件
    //工具栏的布局：工具栏可能使用了布局管理器，例如QHBoxLayout或QVBoxLayout。在这种情况下，直接获取工具栏的宽度和高度可能不会得到你期望的结果，因为布局管理器可能会根据其内部的控件动态调整工具栏的大小。
    //解决方案：考虑使用布局的宽度和高度，或者考虑在布局中直接设置按钮的位置和大小。
    // QPushButton * btn = new QPushButton("啊啊",toolbar);
    // qDebug()<< toolbar->width() << toolbar->height();
    // btn->resize(43,30);
    // btn->move(0,50);
    QPushButton * btn = new QPushButton("啊啊",this);
    toolbar->addWidget(btn);

    //输出坐标//控件,客户区,屏幕窗口
    // qDebug() << btn->x() << btn->y();
    // qDebug() << toolbar->x() << toolbar->y();
    // qDebug() << btn->geometry().x() << btn->geometry().y();
    // qDebug() << toolbar->frameGeometry().x() << toolbar->frameGeometry().y();


    //状态栏
    QStatusBar * stb = statusBar();
    //设置到窗口中
    this->setStatusBar(stb);
    //放标签控件
    QLabel * label = new QLabel("提示信息",this);
    stb->addWidget(label);

    QLabel * label2 = new QLabel("右侧提示信息",this);
    stb->addPermanentWidget(label2);

    //铆接部件(浮动窗口)
    QDockWidget * dock = new QDockWidget("浮动",this);
    addDockWidget(Qt::BottomDockWidgetArea,dock);//核心部件的下面
    //设置后期停靠区域,只允许上下
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    //设置中心部件
    QTextEdit * textedit = new QTextEdit("记事本",this);
    this->setCentralWidget(textedit);
}

MainWindow::~MainWindow() {}







