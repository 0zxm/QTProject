#include "tcpmailclient.h"

TCPMailClient::TCPMailClient(const QString &host, quint16 port, QObject *parent)
    : QObject{parent} {
  QSslSocket *socket = new QSslSocket(this);
  this->ssl = socket;

  QObject::connect(ssl, &QSslSocket::encrypted, [=]() {
    this->isentrcyed = true;
    qDebug() << "连接成功";
  });

  QObject::connect(ssl, &QSslSocket::connected, this,[]() {
        qDebug() << "已连接到SMTP服务器";
    });

  QObject::connect(ssl, &QSslSocket::errorOccurred, this,[](QAbstractSocket::SocketError socketError){
        qDebug() << "发生错误:" << socketError;
    });

  ssl->connectToHostEncrypted(host, port);

  // 可以连接信号，以确认数据已经发送
  connect(ssl, &QSslSocket::bytesWritten, this, [](qint64 bytes) {
    qDebug() << bytes << "bytes were written to the socket.";
  });
}

void TCPMailClient::send(QString msg) {
  if (ssl->state() == QAbstractSocket::ConnectedState) {
    this->ssl->write(msg.toUtf8());
  } else {
    qDebug() << "SMTP连接未建立";
  }
}

QString TCPMailClient::recieve() {
  // 等待并读取响应
  if (ssl->waitForReadyRead()) {
    QByteArray data = ssl->readAll(); // 读取所有可用数据
    qDebug() << "响应内容:" << data;
    return QString(data);
  }
  return QString();
}

bool TCPMailClient::CanReadLine() { return ssl->canReadLine(); }
