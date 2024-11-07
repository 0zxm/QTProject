#ifndef TCPMAILCLIENT_H
#define TCPMAILCLIENT_H

#include <QObject>
#include <QObject>
#include <QtNetwork>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslKey>
#include <QTcpSocket>
#include <QHostAddress>
#include <QIODevice>
#include <QApplication>
#include <QDebug>

class TCPMailClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPMailClient(const QString &host, quint16 port,QObject *parent = nullptr);

    void send(QString msg);

    QString recieve();

    bool ReadyRead();

private:
    QSslSocket* ssl;
    bool isentrcyed = false;

signals:
};

#endif // TCPMAILCLIENT_H
