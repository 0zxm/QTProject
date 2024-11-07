#ifndef WIDGET_H
#define WIDGET_H

#include "tcpmailclient.h"
#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>
#include <QCoreApplication>
#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void updateTextBrowser(const QString &text); // 定义一个更新响应内容的信号
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void startReciveThread();

    void sendRequest();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    TCPMailClient *mailclient;
    QFuture <void> future;
    bool recieveFlag = true;
};
#endif // WIDGET_H
