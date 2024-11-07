#include "widget.h"
#include "ui_widget.h"
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();

    readData();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::writeData(){
    QFile file;
    file.setFileName("../demo.txt");

    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        //指定编码Qt5
        // stream.setCodec("UTF-8");

        stream << QString("主要看气质") << 2150;
        qDebug() << "文件打开";
        file.close();
    } else {
        qDebug() << "无法打开文件";
    }
}

void Widget::readData(){
    QFile file;
    file.setFileName("../demo.txt");

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        //指定编码Qt5
        // stream.setCodec("UTF-8");

        QString str;
        stream >> str;

        qDebug() << "文件打开";

        cout << str;

        file.close();

    } else {
        qDebug() << "无法打开文件";
    }
}

void Widget::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"open","../","文本文件(*.txt);;c++程序(*.cpp)");

    if(path.isEmpty() == false){
        QFile file;
        file.setFileName("../demo.txt");

        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);

            QString content = stream.readAll();

            ui->textBrowser->setText(content);
        }
    }
}
