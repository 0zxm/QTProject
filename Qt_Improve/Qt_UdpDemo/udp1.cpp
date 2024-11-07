#include "udp1.h"
#include "ui_udp1.h"

Udp1::Udp1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化属性
    ui->MyPort->setText("8888");
    ui->ToPort->setText("9999");
    ui->ToIp->setText("127.0.0.1");//本机
    //实例套接字
    udp = new QUdpSocket(this);

    //绑定自身端口号
    udp->bind(ui->MyPort->text().toInt());

    //点击了发送按钮,发送数据
    connect(ui->pushButton, &QPushButton::clicked, this, &Udp1::sendMessage);

    //接收数据
    connect(udp, &QUdpSocket::readyRead, this, &Udp1::receiveMessage);
}

Udp1::~Udp1()
{
    delete ui;
}

void Udp1::sendMessage() {
    //发送报文
    //书写报文 参数1 内容 2 对方IP //3对方端口
    udp->writeDatagram(ui->Input->toPlainText().toUtf8(), QHostAddress(ui->ToIp->text()), ui->ToPort->text().toInt());//纯文本,无下划线等效果

    //写入聊天记录
    ui->Record->append("My Say: " + ui->Input->toPlainText());

    //清空输入框
    ui->Input->clear();
}

void Udp1::receiveMessage() {
    //获取报文长度
    qint64 size = udp->pendingDatagramSize();

    QByteArray array = QByteArray(size, '0');
    //读取报文
    udp->readDatagram(array.data(), size);

    //将数据同步到聊天记录中
    ui->Record->append(array);
}

void Udp1::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return && event->modifiers() == Qt::ControlModifier) {
        sendMessage();
    }
}
