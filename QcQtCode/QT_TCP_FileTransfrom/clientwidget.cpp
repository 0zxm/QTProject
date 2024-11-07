#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QMenu>
#include <QMessageBox>
ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);

    ui->progressBar->setValue(0);   //进度条初始化

    setWindowTitle("客户端");

    this->isHead = true;

    this->setWindowOpacity(1);


    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //取出接收的内容
        QByteArray buf = tcpSocket->readAll();
        if(QString(buf) == "clean file"){
            this->isHead = true;
        }
        if(true == isHead){
            //接收头
            isHead = false;
            //解析头部信息
            /*
            QString str = "hello##2024";
            str.section("##",0,0);
            */

            //初始化
            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;

            //打开文件
            file.setFileName(fileName);

            bool isOk = file.open(QIODevice::WriteOnly);
            if(false == isOk){
                qDebug() <<  "WriteOnly Error 36";
                tcpSocket->disconnectFromHost();
                tcpSocket->close(); //关闭套接字
                return; //中断函数
            }
            // 弹出对话框,显示接收的文件
            QString str = QString("接收文件:[%1: %2kb]").arg(fileName).arg(fileSize/1024.0);
            // QMessageBox::information(this,"文件信息",str);   //这个会导致文件传过去大小为0???
            qDebug() << "客户端接受文件数据" << str;

            // 设置进度条
            ui->progressBar->setMinimum(0); //最小值
            ui->progressBar->setMaximum(fileSize/1024.0);   //最大值
            ui->progressBar->setValue(0);   //当前值


        }else{
            //文件信息
            qint64 len = file.write(buf);
            if(len > 0){
                recvSize += len;
                qDebug() << len;
            }
            //更新进度条
            ui->progressBar->setValue(recvSize/1024);

            if(recvSize == fileSize){   //文件接收完毕

                tcpSocket->write("file done");

                file.close();
                QMessageBox::information(this,"提示","文件接收完成");
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
                }

            }
    });

}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButton_connect_clicked()
{
    //获取服务器的端口和ip
    QString ip = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip),port);
}

//鼠标按下
void ClientWidget::mousePressEvent(QMouseEvent *ev){
    if(ev->button() == Qt::RightButton){
        qDebug() << "右键";
        QMenu menu(this);
        QAction *knowmeAction = menu.addAction("Knowme");

        QAction *choseAction = menu.exec(ev->globalPos());

        if(knowmeAction == choseAction){
            knowme.setWindowTitle("认识我");
            knowme.setStyleSheet("background-image: url(:/weixin.jpg); background-repeat: no-repeat; background-position: center; background-size: contain;");
            knowme.setFixedSize(380,518);
            knowme.show();
        }
    }
}

