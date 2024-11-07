#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QUdpSocket>
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    //消息类型枚举值
    enum MsgType{Msg,UserlEft,UserEnter};

public:
    //关闭事件
    void closeEvent(QCloseEvent *event);
    Widget(QWidget *parent, QString name);
    ~Widget();

private slots:
    void on_pushButton_quit_clicked();

private:
    Ui::Widget *ui;
signals:
    //关闭窗口发送关闭信号
    void closeWidget();

public:
    void sndMsg(MsgType type); // 广播UDP消息
    void usrEnter(QString username); // 处理新用户加入
    void usrLeft(QString username, QString time); // 处理用户离开
    QString getUsr(); // 获取用户名
    QString getMsg(); // 获取聊天消息
private:
    QUdpSocket *udpsocket; // UDP套接宇
    qint16 port; // 端口
    QString uName; // 用户名
    void ReceiveMessage(); // 接受UDP消息

};
#endif // WIDGET_H
