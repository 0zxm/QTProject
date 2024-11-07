#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //重写定时器的事件
    void timerEvent(QTimerEvent *e)override;

    int id1;//定时器1唯一标识

    int id2;//定时器2唯一标识

    //重写时间过滤器
    bool eventFilter(QObject *, QEvent *)override;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
