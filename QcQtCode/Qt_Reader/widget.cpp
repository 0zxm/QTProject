#include "widget.h"
#include "bookbutton.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/Icon.png"));
    this->setWindowTitle("0zxm's Reader");
    this->setFixedSize(800,600);

    label->setFrameStyle(3);
    label->setFrameShadow(QFrame::Sunken);
    label->setGeometry(10,80,780,500);

    /*水平布局*/
    // 创建一个 QGridLayout 或水平布局QHBoxLayout 并将 nameLabel 添加到其中
    layout = new QGridLayout(this);

    // 为 BookButton 小部件设置布局
    label->setLayout(layout);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_exit_clicked()
{
    this->close();
}


void Widget::on_pushButton_input_clicked()
{
    QStringList bookslist = QFileDialog::getOpenFileNames(this,"打开文件","C:\\Users\\86158\\Desktop\\长恨歌.txt",
    "文本文件(*.txt);");
    //导入书本
    QFile book;
    for(int i = 0; i < bookslist.count(); i++){
        book.setFileName(bookslist[i]);

        QFileInfo bookinfo(book);
        QString bookname = bookinfo.baseName(); //basename获取不带后缀名
        QString bookpath = bookinfo.filePath();

        // QFileIconProvider iconProvider;
        // QIcon bookIcon = iconProvider.icon(bookinfo);

        //创建新本地书籍
        BookButton *localbook = new BookButton(label,bookname,bookpath);

        localbook->book->setFixedSize(120,130);
        localbook->setText(bookname);
        // localbook->setWindowIcon(bookIcon);
        localbook->setStyleSheet("QPushButton{background-image: url(:/bookcover.png);}");
        localbook->show();
        //布局自动换行
        layout->addWidget(localbook,(i + total)  / 5, (i + total) % 5);
    }
    total += bookslist.count();

}

