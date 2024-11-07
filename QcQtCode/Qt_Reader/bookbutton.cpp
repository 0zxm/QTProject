#include "bookbutton.h"
#include "readerwidget.h"

BookButton::BookButton(QWidget *parent,QString bookname,QString bookpath)
    : QLabel{parent}
{
    this->bookNameFont.setFamily("华文新魏");
    this->bookNameFont.setPointSize(17);
    this->nameLabel->setFont(bookNameFont);

    this->setFixedSize(120,175);

    // 设置文本居中对齐
    this->nameLabel->setAlignment(Qt::AlignCenter);

    // 允许文本自动换行
    this->nameLabel->setWordWrap(true);

    this->nameLabel->setText(bookname);
    this->nameLabel->setGeometry(this->book->pos().x(),this->book->pos().y() + 131,120,45);

    connect(this->book,&QPushButton::clicked,[=](){
        qDebug() << "打开" << bookname;
        ReaderWidget *reader = new ReaderWidget;
        reader->initBook(bookpath);
        reader->show();
    });
}
