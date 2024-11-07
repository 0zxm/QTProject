#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>

namespace Ui {
class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = nullptr);
    ~SmallWidget();

    //设置数值
    void setNumber(int num);
    //获取数值
    int getNumber();
private:
    Ui::SmallWidget *ui;
};

#endif // SMALLWIDGET_H
