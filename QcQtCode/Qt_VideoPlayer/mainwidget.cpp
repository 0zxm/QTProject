#include "mainwidget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //改善水平滑动条动画优化
    ui->horizontalSlider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "border: 1px solid skyblue;"
        "background-color: skyblue;"
        "height: 10px;"
        "border-radius: 5px;"
        "}"

        "QSlider::handle:horizontal {"
        "background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.7 white, stop:0.8 rgb(140,212,255));"
        "width: 20px;"
        "border-radius: 10px;"
        "margin-top: -5px;"
        "margin-bottom: -5px;"
        "}"

        "QSlider::sub-page:horizontal {"
        "background: red;"
        "margin: 5px;"
        "border-radius: 5px;"
        "}");
        ui->horizontalSlider_2->setStyleSheet(
            "QSlider::groove:horizontal {"
            "border: 1px solid skyblue;"
            "background-color: skyblue;"
            "height: 10px;"
            "border-radius: 5px;"
            "}"

            "QSlider::handle:horizontal {"
            "background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0.7 white, stop:0.8 rgb(140,212,255));"
            "width: 20px;"
            "border-radius: 10px;"
            "margin-top: -5px;"
            "margin-bottom: -5px;"
            "}"

            "QSlider::sub-page:horizontal {"
            "background: red;"
            "margin: 5px;"
            "border-radius: 5px;"
            "}");

        // 视频播放器初始化参数
        player = new QMediaPlayer(this);
        // player->setNotifyInterval(2000);

        QGraphicsScene *scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);

        videoitem = new QGraphicsVideoItem;
        videoitem->setSize(QSize(380, 290));
        videoitem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene->addItem(videoitem);
        player->setVideoOutput(videoitem);
}
    Widget::~Widget()
    {
        delete ui;
    }
    void Widget::onStateChanged(QMediaPlayer::PlaybackState state){
    }
    void Widget::onDurationChanged(qint64 duration){

    }
    void Widget::onPositionChanged(qint64 positiontime){

    }

    //打开要播放的文件
void Widget::on_open_pushButton_clicked()
{
    QString strCurrentPath = QDir::currentPath();                        //QDir::homePath();//获取系统当前目录
    QString strDlgTitle = "请选择视频文件";
    QString strFilter = "MP4 Files(*.mp4);;All Files(*.*)";//文件过滤器

    QString strFilePath = QFileDialog::getOpenFileName(this,strDlgTitle,strCurrentPath,strFilter);

    //打开文件路径不为空
    if(!strFilePath.isEmpty()){
        QMessageBox::information(this,"提示",strFilePath,QMessageBox::Yes|QMessageBox::No);
    }else{
        QMessageBox::information(this,"错误","文件为空",QMessageBox::Yes);
            return;
    }
    //获取文件信息
    QFileInfo fileInfo(strFilePath);
    ui->filename_label->setText(fileInfo.fileName());

    player->setSource(QUrl::fromLocalFile(strFilePath));
    player->play();
}


void Widget::on_pushButton_play_clicked()
{
    player->play();
}


void Widget::on_pushButton_pause_clicked()
{
    player->pause();
}


void Widget::on_pushButton_slient_clicked()
{
}

