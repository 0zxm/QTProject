#include "mainwindow.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QDebug>
//命名规范
//类名 首字母大写，单词和单词之间首字母大写
//函数名 变量名称 首字母小写，单词和单词之间首字母大写

//快捷键
//注释 ctrl + /
//运行 ctrl + r
//编译 ctrl + b
//缩放字体 ctrl + 滚轮
//查找 ctrl + f
//整行移动 ctrl + shift + 上或下
//帮助文档 f1
//自动对齐 ctrl + i
//重名之间的.h 和 .cpp切换 f4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)//初始化列表
{
    //创建一个按钮
    QPushButton * btn = new QPushButton;
    //btn->show();show默认顶层弹出窗口控件
    //让btn对象 依赖在 mywidget窗口中btn->setParent(this);
    btn->setParent(this);

    //显示文本
    btn->setText("第一个按钮");

    //创建第二关按钮,按照空间的大小创建按钮
    QPushButton * btn2 = new QPushButton("第二个按钮" , this);

    //移动btn2按钮
    btn2->move(100,100);
    //按钮指定大小
    btn2->resize(50,50);
    //重置窗口大小
    resize(600,400);
    //设置固定窗口大小
    setFixedSize(600,400);
    //设置窗口标题
    setWindowTitle("FirstWindows");


    //创建一个自己的按钮对象
    MyPushButton * myBtn = new MyPushButton(this);
    myBtn->setText("我的按钮");
    myBtn->move(200,0);
    myBtn->setParent(this);//设置到对象树上(不用关心对象树上的窗口内存管理)


    //信号和槽signals
    //需求 点击我的按钮 关闭窗口
    //连接函数connect();
    //参数1 信号的发送者 参数2 发送的信号(函数地址) 参数3 信号的接收者 参数4 处理的槽函数
    //松散耦合
    //connect( myBtn,&QPushButton::clicked,this,&MainWindow::close);
    connect( myBtn,&QPushButton::clicked,this,&MainWindow::close);
}

MainWindow::~MainWindow() {
    qDebug() << "mainWindows析构被调用";
}
