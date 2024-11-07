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
void Widget:: writeData(){
    //创建文件对象
    QFile file("../test.txt");

    //打开文件对象,以写入模式打开
    bool isOk = file.open(QIODevice::WriteOnly);
    if(isOk){
        //创建数据流,和file文件关联,file类型是iodecive
        //往数据流里写数据,相当于往文件里写数据
        QDataStream stream(&file);

        stream << QString("写入文件") << 250;
    }
    file.close();
}

void Widget::readData(){
    //创建文件对象
    QFile file("../test.txt");

    //打开文件对象,以只读模式打开
    bool isOk = file.open(QIODevice::ReadOnly);
    if(isOk){
        //创建数据流,和file文件关联,file类型是iodecive
        //读数据
        QDataStream stream(&file);
        //读的时候按写的顺序取数据
        QString str;
        int a;
        stream >> str >> a;
        // qDebug() << str.toUtf8().data() << a;
        cout << str.toUtf8().data() << a;
    }
}
