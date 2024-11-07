#include "readerwidget.h"
#include "ui_readerwidget.h"

ReaderWidget::ReaderWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderWidget)
{
    ui->setupUi(this);
    this->setBaseSize(500,800);
    ui->textBrowser->setStyleSheet("QTextBrowser{background-color:rgb(241,229,201);"
    "background-image:url(:/20190724160601_crbhl.jpg);padding-left: 20px;line-height: 120px;}");
    // 设置CSS样式表，设置每一行的缩进为20px  : line-height: 20px;

    initFont();
}

ReaderWidget::~ReaderWidget()
{
    delete ui;
}
void ReaderWidget::initBook(QString bookpath){
    qDebug() << bookpath;
    QFile book(bookpath);
    book.open(QFile::ReadOnly);

    QByteArray content = book.readAll();
    ui->textBrowser->setText(QString(content));
}

void ReaderWidget::initFont(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("楷体", 18), this, tr("选择字体")); // 默认字体为Arial，字号为12

    if (ok) {
        // 用户点击了“确定”按钮
        // 在这里可以使用用户选择的字体
        qDebug() << "Selected font: " << font.family() << ", Size: " << font.pointSize();
        ui->textBrowser->setFont(font);
    } else {
        // 用户点击了“取消”按钮
        qDebug() << "Font selection canceled";
    }
}
