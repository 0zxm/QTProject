#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(1);
    ui->pushButton_cleanfile->setEnabled(0);

    //监听套接字
    tcpServer = new QTcpServer(this);

    //监听
    tcpServer->listen(QHostAddress::Any,8888);
    this->setWindowTitle("服务器端口为: 8888");


    //未建立连接前,两个按钮不能按
    ui->pushButton_send->setEnabled(false);
    ui->pushButton_setfile->setEnabled(false);

    //如果客户端和服务器成功连接,套接字会自动触发newConnection()
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的通信套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        ui->textEdit->setText(str);//显示到编辑区

        //成功连接后才能选择文件
        ui->pushButton_send->setEnabled(1);
        ui->pushButton_setfile->setEnabled(1);


        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //取客户端的信息
            QByteArray buf = tcpSocket->readAll();
            if(QString(buf) == "file done"){
                //文件接收完毕
                ui->textEdit->append("文件发送完毕");
                file.close();
                //断开客户端端口
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        });
    });
    connect(&timer,&QTimer::timeout,[=]()  {
        //关闭定时器
        this->timer.stop();
        //发送真正文件数据
        this->sendFileData();
    });
}

Server::~Server()
{
    delete ui;
}

void Server::on_pushButton_setfile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"open","../");

    // QStringList filepathlist = QFileDialog::getOpenFileNames(this,"open","../");

    if(false == filepath.isEmpty())     //如果选择文件路径有效
    {
        this->fileName.clear();
        this->fileSize = 0;

        //获取文件信息
        QFileInfo info(filepath);
        this->fileName = info.fileName();
        this->fileSize = info.size();

        this->sendSize = 0;

        //只读方式打开文件,指定文件名
        file.setFileName(filepath);

        bool isOk = file.open(QIODevice::ReadOnly);
        if(false == isOk){
            qDebug() << "只读方式打开文件失败";
        }

        //提示打开文件的路径
        ui->textEdit->append(filepath);

        ui->pushButton_setfile->setEnabled(0);
        ui->pushButton_send->setEnabled(1);
        ui->pushButton_cleanfile->setEnabled(1);
    }
    else{
        qDebug() << __FILE__  <<"选择文件路径无效" << __LINE__ ;
    }
}


void Server::on_pushButton_send_clicked()
{
    //先发送文件头信息  文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头信息
    qint64 len = tcpSocket->write(head.toUtf8().data());
    if(len > 0) //头部文件发送成功
    {
        //发送真正文件信息
        //防止TCP黏包问题,需要通过定时器延时20ms
        this->timer.start(20);
    }
    else
    {
        qDebug() << "头部信息发送失败 line97";
        file.close();
        ui->pushButton_setfile->setEnabled(1);
        ui->pushButton_send->setEnabled(0);
    }
}

void Server::sendFileData(){
    qint64 len = 0;

    do{
        //每次发送的数据大小
        char buf[4*1024] = {0};
        len = 0;

        //往文件中读数据
        len = file.read(buf,sizeof(buf));
        //发送数据,读多少,发多少
        len = tcpSocket->write(buf,len);

        //已发送累加
        sendSize += len;

    }while(len > 0);

    //是否发送文件完毕
    if(sendSize == fileSize){
        ui->textEdit->append(QString("文件%1发送完毕").arg(fileName));
        file.close();

        //把客户端断开
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
}

void Server::on_pushButton_cleanfile_clicked()
{
    this->file.close();
    if(tcpSocket){
        qint64 len = tcpSocket->write("clean file");
        qDebug() << len;
    }else
    {
        qDebug() << "cleanfile按钮函数问题";
        return;
    }
    ui->pushButton_cleanfile->setEnabled(0);
    ui->pushButton_setfile->setEnabled(1);
    ui->pushButton_send->setEnabled(0);
}

