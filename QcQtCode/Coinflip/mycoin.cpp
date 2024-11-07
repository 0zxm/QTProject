#include "mycoin.h"
#include <QTimer>
#include <QSoundEffect>
// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        qDebug() <<QString("图片%1加载失败").arg(btnImg);
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    //监听信号,并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        //设置图片固定大小
        this->setFixedSize( pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断,如果翻完了,将min重置
        if(this->min > max){
            this->min = 1;
            this->isAnimation = false; //动画结束
            timer1->stop();
        }
    });

    //初始化定时器对象
    timer2 = new QTimer(this);
    //监听信号,并且反转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        //设置图片固定大小
        this->setFixedSize( pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断,如果翻完了,将min重置
        if(this->max < min){
            this->max = 8;
            this->isAnimation = false; //动画结束
            timer2->stop();
        }
    });

}
//改变标志的方法
void MyCoin::changeFlag(){
    //如果是正面,翻成反面
    if(this->flag){
        timer1->start(30);
        this->isAnimation = true; //动画开始
        this->flag = false;
    }else{
        timer2->start(30);
        this->isAnimation = true; //动画开始
        this->flag = true;
    }

}
//重写按下事件
void MyCoin::mousePressEvent(QMouseEvent * e){
    if(this->isAnimation || this->isWin){
        return;//如果动画在执行,不做任何事
    }else{
        return QPushButton::mousePressEvent(e);//给父类
    }

}
