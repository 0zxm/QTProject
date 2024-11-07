#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFileIconProvider>
#include <QFont>
#include <QScrollArea>
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

    //书籍区域
    QLabel *label = new QLabel(this);
    QGridLayout *layout;

    //导入到第几行第几列
    int total = 0;
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_input_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
