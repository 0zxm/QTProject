#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mycoin.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
PlayScene::PlayScene(int playlevel){
    QString str = QString("进入了第%1关").arg(playlevel);
    qDebug() << str;
    this->levelNum = playlevel;

    //固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0008.png"));
    //设置标题
    this->setWindowTitle(QString("第%1关").arg(this->levelNum));

    //设置背景
    QPainter painter(this);

    //创建菜单栏
    QMenuBar * bar =  menuBar();
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
    QSoundEffect *flipSound = new QSoundEffect();

    // 设置音效文件路径
    flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));//一定要加::fromLocalFile
    QSoundEffect * mainSound = new QSoundEffect();
    // 设置音效文件路径
    mainSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));//一定要加::fromLocalFile

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height()-10);

    //点击返回
    connect(backBtn, &QPushButton::clicked,[=](){
        qDebug()<<"点击返回按钮";
        //告诉主场景,我返回了,主场景监听backBtn按钮
        QTimer::singleShot(300,this,[=](){
            emit this->chooseSceneBack();//发出自定义信号
        });
    });
    //显示当前关卡
    QLabel  * levellabel = new QLabel(this);
    //对于label,可以设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(QString::number(this->levelNum));
    //设置字体到标签中
    levellabel->setFont(font);
    levellabel->setText(str1);
    levellabel->setGeometry(25, this->height() - 50, 120, 50);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0; i < 4; i++){
        for(int j = 0 ; j < 4; j++){
            this->gameArray[i][j] = config.mData[this->levelNum][i][j];
        }
    }

    //胜利图片显示
    QLabel * winlabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setPixmap(tmpPix);
    winlabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winlabel->setParent(this);
    winlabel->move((this->width()-tmpPix.width()) * 0.5, -tmpPix.height());//悬在高空,让他砸下来

    //显示金币背景图
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){

            QPixmap pix(":/res/BoardNode(1).png");
            QLabel *label = new QLabel;
            label->setParent(this);
            label->setGeometry(0,0,pix.width(),pix.width());
            label->setPixmap(pix);
            label->move(i*50+57,j*50+200);
            QString str;
            if(gameArray[i][j] == 1){
               //显示金币
                str= ":/res/Coin0001.png";
            }else{
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(i*50+59,j*50+204);

            //给金币赋属性值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将金币放入金币的二维数组中,以便后期维护
            coins[i][j] = coin;

            //监听对金币按钮的点击事件
            connect(coin,&QPushButton::clicked,[=](){
                flipSound->play();


                //点击瞬间禁用按钮
                for(int i = 0; i < 4; i++){
                    for(int j = 0; j < 4; j++){
                        this->coins[i][j]->isWin = true;
                    }
                }


                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 1 ? 0 : 1;

                //反转周围金币,延时反转
                QTimer ::singleShot(300,this,[=](){
                    if(coin->posX + 1 <= 3){//周围的右侧硬币反转条件
                        coins[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 1 ? 0 : 1;
                    }
                    if(coin->posX - 1 >= 0){//周围的左侧硬币反转条件
                        coins[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 1 ? 0 : 1;
                    }
                    if(coin->posY + 1 <= 3){//周围的上侧硬币反转条件
                        coins[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 1 ? 0 : 1;
                    }
                    if(coin->posY - 1 >= 0){//周围的下侧硬币反转条件
                        coins[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 1 ? 0 : 1;
                    }

                    //翻完金币后解除禁用按钮
                    for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                            this->coins[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i  = 0; i < 4; i++){
                        for(int j = 0; j < 4; j++){
                            if(this->gameArray[i][j] == false){
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin){
                        //胜利了
                        qDebug() << "游戏胜利";
                        //将所有按钮的胜利标志改为true
                        for(int i = 0; i < 4; i++){
                            for(int j = 0; j < 4; j++){
                                coins[i][j]->isWin = true;
                            }
                        }
                        //砸下胜利图片
                        mainSound->setLoopCount(-1);
                        mainSound->play();
                        //创建动态对象
                        QPropertyAnimation * animation = new QPropertyAnimation(winlabel,"geometry");//参数一谁来执行动画
                        //设置动画时间间隔
                        animation->setDuration(200);

                        //起始位置
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        //结束位置
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y() +174,winlabel->width(),winlabel->height()));

                        //设置弹跳曲线
                        animation->setEasingCurve(QEasingCurve::InElastic);

                        //执行动画
                        animation->start();

                        //自动跳转下一关
                        QTimer::singleShot(350,this,[=](){
                            qDebug() << "自动跳转";
                            winlabel->hide();
                            this->hide();
                            emit this->passLevel(this->levelNum);
                        });
                    }
                });
            });
        }
    }
}

//初始化游戏场景
//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
