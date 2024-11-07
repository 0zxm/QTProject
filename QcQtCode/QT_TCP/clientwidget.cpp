#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    ui->textEdit_read->setReadOnly(1);

    tcpSocket = NULL;

    setWindowTitle("客户端");
    //分配空间,指定父对象
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::connected,[=](){
        this->coned = true;
        ui->textEdit_read->setText("成功和服务器建立连接");
    });

    //处理接收数据
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //从通信套接字中取出内容
        QByteArray array = tcpSocket->readAll();
        ui->textEdit_read->append("Server: " + array);
    });

    // 创建一个 QShortcut 对象，设置快捷键为 Ctrl + Enter，绑定到输入框 ui->input 上
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return), ui->textEdit_write);

    // 连接 shortcut 的 activated 信号到 lambda 函数
    connect(shortcut, &QShortcut::activated, [=]() {
        // 当快捷键被触发时，模拟点击发送按钮
        ui->pushButton_send->click();
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_connect_clicked()
{
    //获取服务器ip和端口
    QString ip  = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);

}


void ClientWidget::on_pushButton_send_clicked()
{
    if(!this->coned){
        return;
    }
    //获取文本框内容
    QString str = ui->textEdit_write->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());

    ui->textEdit_write->clear();

    ui->textEdit_read->append(str);
}


void ClientWidget::on_pushButton_close_clicked()
{
    //主动和对方断开连接
    this->coned = false;
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

