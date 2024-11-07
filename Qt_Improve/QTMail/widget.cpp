#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->resize(600, 400);
    mailclient = new TCPMailClient("smtp.163.com", 465);

    // 连接信号到槽
    connect(this, &Widget::updateTextBrowser, [this](const QString &text) {
        // 通过触发信号回到ui线程更新
        ui->textBrowser->append(text);
    });
    startReciveThread();
}

Widget::~Widget() {
    on_pushButton_2_clicked();
    delete ui;
}

void Widget::startReciveThread() {
    future = QtConcurrent::run([=]() {
        recieveFlag = true;
        while (recieveFlag) {
            QString text = this->mailclient->recieve();
            if (text.isEmpty()){
                continue;
            }
            emit this->updateTextBrowser(text); // 发送信号
            QThread::msleep(500);               // 避免过度占用CPU
        }
    });
}

void Widget::sendRequest() {
    QFuture<void> sendFuture = QtConcurrent::run([=]() {
        // 每发送一次会报错两行  QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread
        // 因为套接字是在主线程创建的,所以套接字的QSocketNotifier也要在主线程
        this->mailclient->send("HELO myfriend\r\n");
        QThread::msleep(500);

        this->mailclient->send("AUTH LOGIN\r\n");
        QThread::msleep(500);

        // 发送用户名
        QString username = "m15813109801@163.com";
        QString encodeUsrName  = username.toUtf8().toBase64();
        this->mailclient->send(QString("%1\r\n").arg(encodeUsrName));
        QThread::msleep(500);

        // 发送授权码
        QString password = "MYnwt6tQtEHKZpLN";
        QString encodepwd = password.toUtf8().toBase64();
        this->mailclient->send(QString("%1\r\n").arg(encodepwd));
        QThread::msleep(500);

        this->mailclient->send("MAIL FROM:<m15813109801@163.com>\r\n");
        QThread::msleep(500);

        this->mailclient->send("RCPT TO:<m15813109801@163.com>\r\n");
        QThread::msleep(500);

        this->mailclient->send("DATA\r\n");
        QThread::msleep(500);

        this->mailclient->send("FROM:m15813109801@163.com\r\n");
        QThread::msleep(500);

        this->mailclient->send("SUBJECT: 测试邮件\r\n");
        QThread::msleep(500);

        this->mailclient->send("TO:m15813109801@163.com\r\n");
        QThread::msleep(500);

        this->mailclient->send("\r\n");
        QThread::msleep(500);

        this->mailclient->send("这是一封测试邮件\r\n");
        QThread::msleep(500);

        this->mailclient->send(".\r\n");
        QThread::msleep(500);

        this->mailclient->send("QUIT\r\n");
    });
    // 如果需要，可以在这里使用sendFuture
}

void Widget::on_pushButton_2_clicked() {
    recieveFlag = false;
    if (!future.isFinished()) {
        future.cancel();          // 请求取消任务
        future.waitForFinished(); // 等待任务完成
    }
    QApplication::quit();
}

void Widget::on_pushButton_clicked() {
    sendRequest();
}
