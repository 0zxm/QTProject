#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
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

    // 初始化变量
    bool mousepress = false;
    QPoint movepoint;
    QPoint M_mousepoint;

    //重写绘画事件完成背景设置
    void paintEvent(QPaintEvent * paintevent)override;

    //鼠标拖动窗口实现移动
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev) override;
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev) override;
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev) override;

// private slots:
//     void on_pushButton_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
