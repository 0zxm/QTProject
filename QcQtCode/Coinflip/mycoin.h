#ifndef MYCOIN_H
#define MYCOIN_H
#include <QString>
#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);//参数代表传入的是金币还是银币

    //属性
    int posX;
    int posY;
    int min = 1;
    int max = 8;
    QTimer *timer1;//正反翻面的定时器
    QTimer *timer2;
    bool flag; //代表正面还是反面

    //执行动画标志
    bool isAnimation = false;

    //改变标志的方法
    void changeFlag();

    //重写按下事件
    void mousePressEvent(QMouseEvent * e);

    //是否胜利
    bool isWin = false;

signals:
};

#endif // MYCOIN_H
