#ifndef WIDGET_H
#define WIDGET_H
#include <QImage>
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

    //绘图事件
    void paintEvent(QPaintEvent *) override;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
