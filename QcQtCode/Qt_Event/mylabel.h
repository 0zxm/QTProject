#ifndef MYLABEL_H
#define MYLABEL_H
#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);

    // //鼠标进入
    // void enterEvent(QEnterEvent *event);
    // //鼠标离开事件
    // void leaveEvent(QEvent *event);

    //鼠标按下
    virtual void mousePressEvent(QMouseEvent *ev) override;
    //鼠标释放
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    //鼠标移动
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    //通过事件分发器,拦截事件
    bool event(QEvent * e)override;//返回值为true,表示用户处理,不向下分发

signals:
};

#endif // MYLABEL_H
