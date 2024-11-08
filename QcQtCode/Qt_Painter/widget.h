#ifndef WIDGET_H
#define WIDGET_H
#include <QPaintEvent>
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

    int Posx, Posy;
    //绘图事件
    void paintEvent(QPaintEvent *event);//[virtual protected] void QWidget::paintEvent(QPaintEvent *event)

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
