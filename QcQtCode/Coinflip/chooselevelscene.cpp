#include "chooselevelscene.h"
#include "mypushbutton.h"
#include "qsoundeffect.h"
#include <QMenuBar>
#include <QMenu>
#include <qpainter.h>
#include <QTimer>
#include <QLabel>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置关卡场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("关卡选择");

    //创建菜单栏
    QMenuBar * bar =  menuBar();
    bar->setStyleSheet("background-color: #ADD8E6;");
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出,实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    // 创建一个QSoundEffect对象
    QSoundEffect *soundEffect = new QSoundEffect();

    // 设置音效文件路径
    soundEffect->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));//一定要加::fromLocalFile


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height()-10);

    //点击返回
    connect(backBtn, &QPushButton::clicked,[=](){
        //qDebug()<<"点击返回按钮";
        //告诉主场景,我返回了,主场景监听backBtn按钮
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();//发出自定义信号
        });
    });


    //创建关卡
    for(int i = 0; i < 20; i++){

        int x = i % 4 * 78 + 10;
        int y = i / 4 * 88 + 128;


        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(x, y);

        //监听每个按钮的监听事件
        connect(menuBtn, &QPushButton::clicked,[=](){
            qDebug() << QString("你选择的是第%1关").arg(i + 1);

            //进入到游戏场景
            this->hide();//隐藏选关场景
            play = new PlayScene(i + 1);
            play->show();//显示关卡场景


            /*要在这个大connect里面,否则无效,我也不知道为什么
             *
            */
            //函数指针->函数地址
        });

        QLabel *textlabel = new QLabel(this);
        textlabel->setFixedSize(menuBtn->width(),menuBtn->height());
        textlabel->setText(QString::number(i + 1));
        textlabel->move(x-1, y-1);

        QFont font;
        font.setFamily("华文新魏");
        font.setPointSize(12);
        font.setBold(false);
        textlabel->setFont(font);
        //设置label上的文字对齐方式水平居中和垂直居中
        textlabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透
        textlabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
    connect(play,&PlayScene::passLevel,this,[=](int levelNum){
        qDebug() << "创建新关卡";
        this->passedLevel[levelNum] = true;
        play->hide();
        play = nullptr;
        play = new PlayScene(levelNum+ 1);
        play->show();
        // delete nowplay;
        // nowplay = nullptr;
    });
    connect(play,&PlayScene::chooseSceneBack,this,[=](){
        qDebug() << "游戏场景退回关卡选择";
        play->hide();
        this->show();
        delete play;

    });

}

//重写paintEVent事件
void ChooseLevelScene::paintEvent(QPaintEvent * ){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上的图标
    pix.load(":/res/Title.png");

    //缩放图片代码
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

