#ifndef UDP2_H
#define UDP2_H

#include <QWidget>
#include<QUdpSocket>
#include <QShortcut>
namespace Ui {
class udp2;
}

class udp2 : public QWidget
{
    Q_OBJECT

public:
    explicit udp2(QWidget *parent = 0);
    ~udp2();

private:
    Ui::udp2 *ui;
public:
    QUdpSocket* udp;
};

#endif // UDP2_H
