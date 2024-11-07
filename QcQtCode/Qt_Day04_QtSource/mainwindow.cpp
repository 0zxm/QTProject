#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->actionnew->setIcon(QIcon("C:\\Users\\86158\\Pictures\\Feedback\\{606E9934-E6FC-4BD2-846D-61136D7691AE}\\Capture001.png"));

    //将资源拷贝到项目下,新建Qt资源文件
    //将图片文件 拷贝到项目位置下
    //右键项目->添加新文件 - Qt ->Qt recourse File->给资源文件起名
    //res 生成 res.qrc4
    //open in editor 编辑资源
    //添加前缀添加文件
    //使用“:+ 前缀名 +文件名”
    //使用添加Qt图片资源 ": + 前缀名 + 文件名 "
    ui->actionnew->setIcon(QIcon(":/new/prefix1/image/OIP-C.jfif"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
