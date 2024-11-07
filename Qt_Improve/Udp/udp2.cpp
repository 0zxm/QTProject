#include "udp2.h"
#include "ui_udp2.h"

udp2::udp2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udp2)
{
    ui->setupUi(this);

    //设置属性
    ui->myport->setText("9999");
    ui->toport->setText("8888");
    ui->toip->setText("127.0.0.1");

    //创建套接字
    udp = new QUdpSocket(this);
    //绑定自身端口号
    udp->bind(ui->myport->text().toInt());
    //点击发送按钮，发送报文
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        //输入内容纯文本发送用text edit的toPlainText函数(该函数为QString类型，利用成员函数
        //toUtf8()转换为QByteArray)，带有颜色等复杂特效的文字用
        //toHtml函数
        //书写报文 参数1 内容 参数2 对方IP 参数3 对方端口
        udp->writeDatagram(ui->input->toPlainText().toUtf8(),QHostAddress(ui->toip->text()),
        ui->toport->text().toInt());

        //聊天记录窗口进行记录
        ui->record->append("my say:"+ui->input->toPlainText());
        //清空输入
        ui->input->clear();
    });

    //接收数据
    //发送数据后，套接字接收端会自动有一个readyRead信号
    connect(udp,&QUdpSocket::readyRead,[=](){
        //获取报文长度
        qint64 size = udp->pendingDatagramSize();
        QByteArray array = QByteArray(size,0);
        //char* QByteArray::data()
        //读取报文
        udp->readDatagram(array.data(),size);
        //将数据同步到聊天记录中
        ui->record->append(array);
    });

    // 创建一个 QShortcut 对象，设置快捷键为 Ctrl + Enter，绑定到输入框 ui->input 上
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return), ui->input);

    // 连接 shortcut 的 activated 信号到 lambda 函数
    connect(shortcut, &QShortcut::activated, [=]() {
        // 当快捷键被触发时，模拟点击发送按钮
        ui->sendBtn->click();
    });

}

udp2::~udp2()
{
    delete ui;
}
