#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>   //通信套接字
#include <QHostAddress>
#include <QShortcut>    //快捷方式
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket * tcpSocket;

    bool coned = false;
};

#endif // CLIENTWIDGET_H
