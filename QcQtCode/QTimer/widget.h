#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer> //定时器头文件
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

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Widget *ui;

    QTimer * myTimer;   //定时器对象
};
#endif // WIDGET_H
