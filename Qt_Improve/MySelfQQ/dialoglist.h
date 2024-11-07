#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>
#include <QToolButton>
#include <QList>
#include <QVector>
#include <QMessageBox>
namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = nullptr);
    ~DialogList();

    bool widgetisShow[9];//九个用户窗口是否被创建

private:
    Ui::DialogList *ui;
};

#endif // DIALOGLIST_H
