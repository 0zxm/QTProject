#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>   //监听套接字
#include <QTcpSocket>   //通信套接字
#include <QShortcut>    //快捷方式
QT_BEGIN_NAMESPACE
namespace Ui {
class ServerWidget;
}
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::ServerWidget *ui;

private:
    QTcpSocket * tcpSocket; //通信套接字
    QTcpServer * tcpServer; //监听套接字

    qint16 sons = 0;
};
#endif // SERVERWIDGET_H
