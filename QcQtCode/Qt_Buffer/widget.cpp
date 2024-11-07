#include "widget.h"
#include "ui_widget.h"
#include <QBuffer>
#include <qdatastream.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QByteArray array;

    //创建内存文件
    // QBuffer memfile(this);
    QBuffer memfile(&array);

    memfile.open(QIODeviceBase::WriteOnly);

    memfile.write("1111111111111111111");
    memfile.write("222222222222222222");

    memfile.close();

    qDebug() << memfile.buffer();
    qDebug() << "array" << array;


    QBuffer memfile1;
    memfile1.open(QIODeviceBase::WriteOnly);
    QDataStream stream(&memfile1);
    stream << QString("测试") << 250;
    memfile1.close();

    qDebug() <<QString(memfile1.buffer()).toUtf8().data();

    memfile1.open(QIODeviceBase::ReadOnly);
    QDataStream out;
    out.setDevice(&memfile1);
    QString str;
    int a;
    out >> str >> a;
    memfile1.close();
    qDebug() << str << a;


}

Widget::~Widget()
{
    delete ui;
}
