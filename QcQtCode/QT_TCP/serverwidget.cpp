#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);


    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字,指定父对象,自动回收空间
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,8888);

    ui->textEdit_read->setReadOnly(1);

    this->setWindowTitle("服务器:8888");

    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        this->sons++;

        //获取对方的ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        QString tmp = QString("[%1:%2]:成功连接!").arg(ip).arg(port);

        ui->textEdit_read->setText(tmp);

        //处理接收数据
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            ui->textEdit_read->append("Client: " + array);
        });

        connect(tcpSocket,&QTcpSocket::disconnected,[=](){
            this->sons--;
        });
    });


    // 创建一个 QShortcut 对象，设置快捷键为 Ctrl + Enter，绑定到输入框 ui->input 上
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Return), ui->textEdit_write);

    // 连接 shortcut 的 activated 信号到 lambda 函数
    connect(shortcut, &QShortcut::activated, [=]() {
        // 当快捷键被触发时，模拟点击发送按钮
        ui->pushButton_send->click();
    });

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_pushButton_send_clicked()
{
    if(tcpSocket == NULL){
        return;
    }
    //获取编辑区内容
    QString str = ui->textEdit_write->toPlainText();
    //给对方发送数据,是通信套接字tcpSocket
    tcpSocket->write(str.toUtf8().data());  //转成char*类型

    ui->textEdit_write->clear();

    ui->textEdit_read->append(str);
}


void ServerWidget::on_pushButton_close_clicked()
{
    if(this->sons == 0){
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
    this->sons = 0;
}

