#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "mycoin.h"
#include <QMainWindow>
#include <QSoundEffect>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr,int playlevel = 1);

    PlayScene(int playlevel = 1);

    //重写绘图事件
    void paintEvent(QPaintEvent *)override;

    int levelNum; //记录关卡

    int gameArray[4][4];//用二维数组保存初始化关卡
    MyCoin * coins[4][4];//关卡的金币数组

    bool isWin = false;//关卡是否胜利的标志
signals:
    //返回信号
    void chooseSceneBack();
    //胜利
    void passLevel(int levelNum);
};

#endif // PLAYSCENE_H
