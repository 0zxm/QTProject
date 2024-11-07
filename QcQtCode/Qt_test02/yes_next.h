#ifndef YES_NEXT_H
#define YES_NEXT_H

#include <QWidget>

namespace Ui {
class Yes_Next;
}

class Yes_Next : public QWidget
{
    Q_OBJECT

public:
    explicit Yes_Next(QWidget *parent = nullptr);
    ~Yes_Next();

private:
    Ui::Yes_Next *ui;
};

#endif // YES_NEXT_H
