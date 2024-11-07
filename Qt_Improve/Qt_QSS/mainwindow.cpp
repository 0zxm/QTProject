#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet("QPushButton{color:blue;}");//color:字体颜色
    // 同时设置多个
    ui->pushButton->setStyleSheet("QPushButton,QTextEdit{color:blue;}");//color:字体颜色

    //更改spinbox子控件背景颜色
    ui->spinBox->setStyleSheet("QSpinBox::up-arrow{background-color:green;}");
    //伪状态
    ui->pushButton->setStyleSheet("QPushButton:hover{color:green;background-color:rgb(15,200,255);}");

    this->setStyleSheet("QTextEdit#textEdit:background-color:blue;}");

    ui->textEdit->setStyleSheet("QTextEdit{background-image: url(:/OIP-C.png);Background-Attchment:fixed;}");

    //改善水平滑动条动画优化
    ui->horizontalSlider->setStyleSheet(
        "QSlider::groove:horizontal {" //滑块轨道
        "border: 1px solid rgba(255,255,255,255);" //边框
        "background-color: rgba(0,155,210,55);"
        "height:3px;"
        "border-radius: 2px;"  //圆框边角
        "}"


        "QSlider::handle:horizontal {"
        "background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.7 skyblue, stop:0.8 "
        "rgb(255,255,255));"
        "width: 5px;"
        "height: 10px;"
        "border-radius: 10px;"
        "border-radius: 50%;"
        "margin-top: -5px;"
        "margin-bottom: -5px;"
        "}"

        "QSlider::sub-page:horizontal {"
        "background: black;"
        "margin: 2px;"
        "border-radius: 5px;"
        "}");
}

MainWindow::~MainWindow()
{
    delete ui;
}
