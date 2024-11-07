#ifndef WIDGET_H
#define WIDGET_H
#include "teacher.h"
#include "student.h"
#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void print();

private:
    Ui::Widget *ui;

    Teacher * t;
    Student * s;

    void classOver();
};
#endif // WIDGET_H
