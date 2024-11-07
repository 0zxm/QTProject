#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

    //鼠标按下
    virtual void mousePressEvent(QMouseEvent *ev) override;

private slots:
    void on_pushButton_connect_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket * tcpSocket;

    QFile file;//文件对象
    QString fileName;   //文件名
    qint64 fileSize;    //文件大小

    qint64 recvSize;   //已经接收文件大小

    bool isHead;

    QWidget knowme;
};

#endif // CLIENTWIDGET_H
