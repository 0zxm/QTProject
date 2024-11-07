#ifndef UDP1_H
#define UDP1_H

#include <QWidget>
#include <QUdpSocket>
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Udp1 : public QWidget
{
    Q_OBJECT

public:
    Udp1(QWidget *parent = nullptr);
    ~Udp1();

    void keyPressEvent(QKeyEvent *event);

    void receiveMessage();

    void sendMessage();

private:
    Ui::Widget *ui;
public:
    //套接字
    QUdpSocket *udp;
};
#endif // UDP1_H
