#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QColorDialog>
#include <QString>
#include <QMessageBox>
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
    void initWidgetUi();

private slots:
    void on_pushButton_color_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_bold_clicked(bool checked);

    void on_pushButton_italic_clicked();

    void on_pushButton_underline_clicked();

    void on_comboBox_size_currentIndexChanged(int index);

    void on_pushButton_send_clicked();

private:
    Ui::Widget *ui;
    QColor color;
};
#endif // WIDGET_H
