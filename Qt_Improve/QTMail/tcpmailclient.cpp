#include "tcpmailclient.h"

TCPMailClient::TCPMailClient(const QString &host, quint16 port,QObject *parent)
    : QObject{parent}
{
    QSslSocket *socket = new QSslSocket(this);
    this->ssl = socket;

    QObject::connect(ssl,&QSslSocket::encrypted,[this](){
        this->isentrcyed = true;
        qDebug() << "连接成功";
    });

    // 可以连接信号，以确认数据已经发送
    connect(ssl, &QSslSocket::bytesWritten, this, [](qint64 bytes) {
        qDebug() << bytes << "bytes were written to the socket.";
    });

    ssl->connectToHostEncrypted(host,port);
}

void TCPMailClient::send(QString msg)
{
    this->ssl->write(msg.toUtf8());
}

QString TCPMailClient::recieve()
{
    // 等待并读取响应
    if (ssl->waitForReadyRead()) {
        QByteArray data = ssl->readAll();  // 读取所有可用数据
        qDebug() << "响应内容:" << data;
        return data;
    }
    return NULL;

}

bool TCPMailClient::ReadyRead()
{
    return ssl->canReadLine();
}

