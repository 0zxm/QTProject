#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>   //监听套接字
#include <QTcpSocket>   //通信套接字
#include <QFile>
#include <QFileDialog>
#include <QFileInfo> //文件信息
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server;
}
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

    void sendFileData();
private slots:
    void on_pushButton_setfile_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_cleanfile_clicked();

private:
    Ui::Server *ui;

    QTcpServer * tcpServer;
    QTcpSocket * tcpSocket;

    QFile file;//文件对象
    QString fileName;   //文件名
    qint64 fileSize;    //文件大小

    qint64 sendSize;   //已经发送文件大小

    QTimer timer;    //定时器

    void cleanfile();

};
#endif // SERVER_H
