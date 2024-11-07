#ifndef READERWIDGET_H
#define READERWIDGET_H

#include <QWidget>
#include <QFile>
#include <QFontDialog>

namespace Ui {
class ReaderWidget;
}

class ReaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderWidget(QWidget *parent = nullptr);
    ~ReaderWidget();
    void initBook(QString bookpath);

    //内容字体
    QFont textFont;

    //初始化字体
    void initFont();
private:
    Ui::ReaderWidget *ui;
};

#endif // READERWIDGET_H
