#ifndef BOOKBUTTON_H
#define BOOKBUTTON_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QFile>
class BookButton : public QLabel
{
    Q_OBJECT
public:
    explicit BookButton(QWidget *parent = nullptr,QString bookname = "unknown",QString bookpath = "unknown");
    QPushButton * book = new QPushButton(this);
    QLabel *nameLabel = new QLabel(this);

    //书名字体
    QFont bookNameFont;

signals:
};

#endif // BOOKBUTTON_H
