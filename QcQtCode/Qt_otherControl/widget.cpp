#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //栈控件使用
    //设置默认定位到scollArea
    ui->stackedWidget->setCurrentIndex(0);
    //scollArea按钮
    connect(ui->btn_scollArea, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    //toolBox按钮
    connect(ui->btn_ToolBox, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    //TabWidget按钮
    connect(ui->btn_TabWidget, &QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    //下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("拖拉机");
    //点击按钮,选中选项
    connect(ui->btn_select, &QPushButton::clicked,[=](){
        //ui->comboBox->setCurrentIndex(2);
        ui->comboBox->setCurrentText("拖拉机");
    });
    //利用QLable显示图片Qt中叫Pixmap
    ui->label->setPixmap(QPixmap(":/Image/butterfly.png"));//文件路径

    //利用QLable显示动图Qt中要求gif格式
    QMovie *mv = new QMovie(":/Image/mario.gif");
    ui->label->setMovie(mv);
    mv->setCacheMode(QMovie::CacheAll); // 可选，设置缓存模式

    //QMovie::CacheNone：不缓存任何帧，每次需要显示新帧时都会从文件中读取。这样可以减少内存占用，但可能会导致动画显示不流畅。

    //QMovie::CacheAll：缓存所有帧，将整个动画文件加载到内存中。这样可以提高动画的加载速度和显示流畅度，但会占用较多的内存。

    //QMovie::CacheMode：根据需要缓存帧，动画帧将根据需要进行加载和释放，以平衡内存占用和加载速度。
    mv->setSpeed(1000); // 可选，设置播放速度
    //播放
    mv->start();

    // 循环播放
    QObject::connect(mv, &QMovie::frameChanged, [=]() {
        if (mv->currentFrameNumber() == mv->frameCount() - 1) {
            mv->jumpToFrame(0);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}
