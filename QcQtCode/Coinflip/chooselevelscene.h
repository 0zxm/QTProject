#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include "playscene.h"
#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);


    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene * play = NULL;

    bool passedLevel[20] = {false}; //已通过关卡
signals:
    //写一个自定义信号，告诉主场景  点击了返回
    void chooseSceneBack();


public slots:


};

#endif // CHOOSELEVELSCENE_H
