#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(600,400);
    mailclient = new TCPMailClient("smtp.163.com",465);

    // 连接信号到槽
    connect(this, &Widget::updateTextBrowser, [this](const QString &text) {
        ui->textBrowser->append(text);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::startReciveThread()
{
    future = QtConcurrent::run([=]() {
        while (recieveFlag) {
            if(!this->mailclient->ReadyRead()){
                continue;
            }
            QString text = this->mailclient->recieve();
            emit this->updateTextBrowser(text); // 发送信号
            QThread::msleep(500); // 避免过度占用CPU
        }
    });
}

void Widget::sendRequest()
{
    QFuture<void> sendFuture = QtConcurrent::run([=]() {
        this->mailclient->send("HELO myfriend");
        qDebug() << "发送第一条";
        QThread::msleep(500);
        this->mailclient->send("AUTH LOGIN");
        qDebug() << "发送第二条";
        QThread::msleep(500);
    });
    // 如果需要，可以在这里使用sendFuture
}

void Widget::on_pushButton_2_clicked()
{
    recieveFlag = false;
    if (!future.isFinished()) {
        future.cancel(); // 请求取消任务
        future.waitForFinished(); // 等待任务完成
    }
    QApplication::quit();
}

void Widget::on_pushButton_clicked()
{
    startReciveThread();
    QThread::msleep(100);
    sendRequest();
}
