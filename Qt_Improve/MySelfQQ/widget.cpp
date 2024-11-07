#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent,QString name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(name);

    ui->toolButton_bold->setCheckable(true);
    ui->toolButton_bold->setToolTip("加粗");
    ui->toolButton_itital->setCheckable(true);
    ui->toolButton_itital->setToolTip("倾斜");
    ui->toolButton_underline->setCheckable(true);
    ui->toolButton_underline->setToolTip("下划线");

    ui->toolButton_color->setToolTip("改颜色");
    ui->toolButton_save->setToolTip("保存");
    ui->toolButton_clear->setToolTip("清屏");

    //选中有蓝色背景
    ui->UserTblWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //选中整行
    ui->UserTblWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //初始化
    udpsocket = new QUdpSocket(this);
    //用户名获取
    uName = name;
    //端口号
    this->port = 9999;

    //绑定端口号 绑定模式 共享地址，断线重连
    udpsocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);

    //发送新用户进入消息
    sndMsg(UserEnter);

    //点击发送按钮发送消息
    connect(ui->pushButton_send,&QPushButton::clicked,[=](){
        sndMsg(Msg);
    });
    //监听别人发送的数据
    connect(udpsocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMessage);

    //点击按钮,关闭窗口
    connect(ui->pushButton_quit,&QPushButton::clicked,this,[=](){
        this->close();
    });

    //////////////////////////辅助功能///////////////////////////
    //字体
    connect(ui->fontComboBox,&QFontComboBox::currentFontChanged,[=](const QFont& font){
        ui->msgTextEdit->setFont(font);
        ui->msgTextEdit->setFocus();
    });
    //字号
    void(QComboBox:: *cbxsignal )(const QString& text) = &QComboBox::currentTextChanged;
    connect(ui->comboBox,cbxsignal,[=](const QString& text){
        ui->msgTextEdit->setFontPointSize(text.toDouble());
        ui->msgTextEdit->setFocus();
    });
    //加粗
    connect(ui->toolButton_bold,&QToolButton::clicked,[=](bool isCheck){
        if(isCheck){
           ui->msgTextEdit->setFontWeight(QFont::Bold);
        }else{
            ui->msgTextEdit->setFontWeight(QFont::Normal);
        }
        ui->msgTextEdit->setFocus();

    });
    //倾斜
    connect(ui->toolButton_itital,&QToolButton::clicked,[=](bool check){
        ui->msgTextEdit->setFontItalic(check);
        ui->msgTextEdit->setFocus();
    });
    //下划线
    connect(ui->toolButton_underline,&QToolButton::clicked,[=](bool check){
        ui->msgTextEdit->setFontUnderline(check);
    });
    //颜色 调用写好的颜色对话框QColorDialog
    connect(ui->toolButton_color,&QToolButton::clicked,[=](){
        QColor color = QColorDialog::getColor(Qt::red);
        ui->msgTextEdit->setTextColor(color);
    });
    //清空聊天记录
    connect(ui->toolButton_clear,&QToolButton::clicked,[=](){
        ui->msgBrowser->clear();
    });
    //保存聊天记录
    connect(ui->toolButton_save,&QToolButton::clicked,[=](){

        if(ui->msgBrowser->document()->isEmpty()){

            QMessageBox::warning(this,"警告","内容不能为空");
            return;
        }
        QString path = QFileDialog::getSaveFileName(this,"保存记录","聊天记录","(*.txt)");
        if(path.isEmpty()){
            QMessageBox::warning(this,"警告","路径不能为空");
            return;
        }else{
            QFile file(path);
            file.open(QIODevice::WriteOnly | QIODevice::Text); // QIODevice::Text打开模式会换行
            QTextStream stream(&file);
            stream << ui->msgBrowser->toPlainText();
            file.close();
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_quit_clicked()
{
    this->close();
}
void Widget::closeEvent(QCloseEvent *event){

    emit this->closeWidget();
    sndMsg(UserlEft);
    //断开套接字
    udpsocket->close();
    udpsocket->destroyed();

    QWidget::closeEvent(event);

}
// 广播UDP消息
void Widget::sndMsg(MsgType type){
    //发送消息分为三类
    //发送的数据 做分段处理 第一段 类型 第二段 用户名  第三段 具体内容
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);

    stream << type << getUsr();//第一段内容添加到流

    switch(type){
    case Msg: //
        if(ui->msgTextEdit->toPlainText().isEmpty()){
            QMessageBox::warning(this,"警告","发送内容不能为空");
            return;
        }
        //第三段 具体内容
        stream << getMsg();
        break;
    case UserEnter: //用户进入
        break;
    case UserlEft: //用户离开
        break;
    default:
        break;
    }
    //书写报文 广播发送
    udpsocket->writeDatagram(array,QHostAddress::Broadcast,port);

}

// 获取聊天消息
QString Widget::getMsg(){

    QString str = ui->msgTextEdit->toHtml();
    //清空输入框
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();//处理连续发送
    return str;
}

void Widget::ReceiveMessage(){
    //拿到数据报文
    qint64 size = udpsocket->pendingDatagramSize();
    QByteArray array(size,0);
    udpsocket->readDatagram(array.data(),size);
    //解析数据
    //第一段 类型,第二段 用户名 第三段 内容

    QDataStream stream(&array,QIODevice::ReadOnly);

    int msgtype;//读取到消息类型
    QString usrname;
    QString msg;

    //获取当前时间
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    stream >> msgtype;

    switch(msgtype){
    case Msg:
        stream >> usrname >> msg;
        //追加聊天记录
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + usrname + "]" + time);
        ui->msgBrowser->append(msg);
        break;
    case UserEnter:
    {
        //更新右侧用户列表
        stream >> usrname;
        usrEnter(usrname);
        break;
    }
    case UserlEft:
        stream >> usrname;
        usrLeft(usrname,time);
    default:
        break;

    }


} // 接受UDP消息格式化

QString Widget::getUsr(){
    return this->uName;
} // 获取用户名


void Widget::usrEnter(QString username){

        bool isempty = ui->UserTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
        if(isempty)
        {
            QTableWidgetItem *usr = new QTableWidgetItem(username);
            //插入行
            ui->UserTblWidget->insertRow(0);
            ui->UserTblWidget->setItem(0,0,usr);

            //追加聊天记录
            ui->msgBrowser->setTextColor(Qt::gray);
            ui->msgBrowser->append(QString("%1上线了").arg(username));
            //在线人数更新
            ui->onlineNum->setText(QString("在线人数: %1").arg(ui->UserTblWidget->rowCount()));

            //广播信息
            sndMsg(UserEnter);
        }
} // 处理新用户加入

void Widget::usrLeft(QString username, QString time){
    //更新右侧tablewidget
    bool isEmpty = ui->UserTblWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(!isEmpty){
        int row = ui->UserTblWidget->findItems(username,Qt::MatchExactly).first()->row();
        ui->UserTblWidget->removeRow(row);
    }
    //追加聊天记录
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->append(QString("%1于%2离开聊天室").arg(username).arg(time));
    //在线人数更新
    ui->onlineNum->setText (QString("在线用户:%1人").arg(ui->UserTblWidget->rowCount()));
} // 处理用户离开



