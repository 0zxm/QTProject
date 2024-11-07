#include "mainscene.h"
#include "qlabel.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QMediaPlayer> //多媒体模块下音效类
#include <QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    ui->menubar->setStyleSheet("background-color: #ADD8E6;");
    //设置固定大小
    this->setFixedSize(320, 588);

    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("0zxm的翻金币小游戏");

    //游戏规则
    QFont font;
    font.setBold(0);
    font.setPointSize(15);
    font.setFamily("华文新魏");

    QLabel *playrule = new QLabel;
    playrule->setFont(font);
    playrule->setText("欢迎来到0zxm的翻金币小游戏,把硬币全部翻成金币,就是游戏胜利");
    playrule->setFixedSize(this->width()*0.615,80);
    playrule->setWordWrap(true); // 设置自动换行
    playrule->setParent(this);
    playrule->move(59, 199);
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });


    //开始音效
    // 创建一个QSoundEffect对象
    QSoundEffect *soundEffect = new QSoundEffect();

    // 设置音效文件路径
    soundEffect->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));//一定要加::fromLocalFile

    //开始按钮的实现
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()/2 - startBtn->width()/2,this->height()*0.7);

    //实例化关卡选择场景
    chooselevelscence = new ChooseLevelScene;

    //监听选择场景返回按钮的场景

    connect(chooselevelscence,&ChooseLevelScene::chooseSceneBack,this,[=](){
        chooselevelscence->hide();
        this->show(); //重新显示主场景

    });

    connect(startBtn,&QPushButton::clicked,[=](){
        qDebug() << "点击了开始按钮";
        // 播放音效
        soundEffect->play();
        startBtn->zoom1();
        startBtn->zoom2();


        //延时进入到选择关卡场景
        QTimer::singleShot(400,this,[=](){
            //自身隐藏
            this->hide();
            //进入到选择关卡的场景
            chooselevelscence->show();

        });

    });

}

void MainScene::paintEvent(QPaintEvent * ){
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(),pix); //按大小拉伸

    //画背景上的图标
    pix.load(":/res/Title.png");

    //缩放图片代码
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}


MainScene::~MainScene()
{
    delete ui;
}
