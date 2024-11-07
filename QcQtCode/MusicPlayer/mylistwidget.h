#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QContextMenuEvent>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = nullptr);

    //重写菜单事件
    void contextMenuEvent(QContextMenuEvent *event) override;


signals:
    void reMove(QListWidgetItem * item);
};

#endif // MYLISTWIDGET_H
