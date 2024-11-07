#include "widget.h"
#include "yes_next.h"
#include "ui_widget.h"
#include <QMovie>
#include <QDialog>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //添加马里奥动画
    QMovie * mario = new QMovie(":/mario.gif");
    ui->marioLabel->setMovie(mario);
    ui->marioLabel->setScaledContents(true); // 将内容缩放以适应控件大小
    //设置播放速度
    mario->setSpeed(150);
    mario->start();

    // 连接按钮的点击事件
    QObject::connect(ui->pushButton_Yes, &QPushButton::clicked, [=](){
        Yes_Next *y = new Yes_Next;
        y->setVisible(true);
        y->setWindowFlag(Qt::WindowStaysOnTopHint);
        //y->setGeometry(100, 100, 400, 400); // 设置窗口位置和大小
        y->setGeometry(600,150,400,600);
        y->show();
        y->raise();
        this->close();
        //exit(0);
    });
    QObject::connect(ui->pushButton_No, &QPushButton::clicked, [=](){

        // 用户点击了 "No" 按钮，继续循环
        while (true) {
            QDialog loopDialog;
            loopDialog.setWindowTitle("循环对话框");
            loopDialog.setWindowFlag(Qt::WindowStaysOnTopHint);
            loopDialog.setModal(true);
            loopDialog.setFixedSize(350, 100); // 设置固定大小

            QLabel *label = new QLabel(&loopDialog);
            label->setText("你在考虑下,接不接受"); // 确保文本正确设置
            label->show();
            label->setGeometry(120, 10, 150, 35); // 设置位置和大小
            //label->setStyleSheet("border: 1px solid black"); // 添加边框以显示位置
            QPalette palette = label->palette();
            palette.setColor(QPalette::Text, QColor(0, 0, 255)); // 设置文本颜色为蓝色
            label->setPalette(palette);

            QPushButton *btnYesLoop = new QPushButton("Yes", &loopDialog);
            QPushButton *btnNoLoop = new QPushButton("No", &loopDialog);
            btnYesLoop->setGeometry(50, 50, 100, 30);
            btnNoLoop->setGeometry(200, 50, 100, 30);

            // 设置父子关系
            btnYesLoop->setParent(&loopDialog);
            btnNoLoop->setParent(&loopDialog);

            // 连接按钮的点击事件
            QObject::connect(btnYesLoop, &QPushButton::clicked, &loopDialog, &QDialog::accept);
            QObject::connect(btnNoLoop, &QPushButton::clicked, &loopDialog, &QDialog::reject);

            // 显示循环对话框
            if (loopDialog.exec() == QDialog::Accepted) {
                // 用户点击了 "Yes" 按钮，退出循环
                Yes_Next *y = new Yes_Next;
                y->setGeometry(600, 150, 400, 400); // 设置窗口位置和大小
                y->show();
                y->raise();
                this->close();
                //exit(0);
                break;
            }
        }
    });



}

Widget::~Widget()
{
    delete ui;
}
