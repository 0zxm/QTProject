#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QPushButton>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <qtextstream.h>
// #include <QTextCodec>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击选取文件的按钮,弹出对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){

        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\86158\\Desktop\\长恨歌.txt","文本文件(*.txt);;c++源文件(*.cpp)");
        //将路径放入到lineedit中
        ui->lineEdit->setText(path);

        //编码格式类
        //QTextCodec * codec  = QTextCodec::codecForName ("gbk");

        //读取内容放入 textedit中
        // QFile默认支持UTF-8
        QFile file(path); //参数就是你读取的文件的路径
        //设置打开方式
        file.open(QIODevice::ReadOnly);//读

        // QByteArray arr = file.readAll();

        QByteArray arr;

        while(!file.atEnd()){ //类似于c++文件流中的EOF
            arr += file.readLine();//读一行,追加
        }
        //将读取到的数据放入textedit中
        ui->textEdit->setText(QString(arr));
        // ui->textEdit->setText(codec->toUnicode(arr));

        file.close();//文件对象关闭

        //进行写入
        file.open(QIODevice::Append); //用追加的方式开始写
        //file.write("\n好诗好诗");
        file.close();


        //FileInfo文件信息类
        QFileInfo info(path);

        qDebug() << "文件大小" << info.size() <<"Byte" << "文件路径" << info.path() << "文件后缀" << info.suffix();
        qDebug() << "创建日期" << info.birthTime().toString("yyyy/MM/dd hh:mm:ss");
        qDebug() << "元数据最后修改日期" << info.metadataChangeTime().toString("yyyy/MM/dd hh:mm:ss");
        qDebug() << "最后修改日期" << info.lastModified().toString("yyyy/MM/dd hh:mm:ss");
        qDebug() << "最后阅读日期" << info.lastRead().toString("yyyy/MM/dd hh:mm:ss");


    });


    //连接保存文件按钮的点击事件到槽函数
    // connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::onSaveButtonClicked);

    //点击保存文件的按钮
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        //获取文件路径
        QString path = ui->lineEdit->text();
        //打开文件进行写入
        QFile file(path);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){ //以写入和文本模式打开文件
            //获取textEdit中的内容
            QString content = ui->textEdit->toPlainText();
            //将内容写入文件
            QTextStream out(&file);
            out << content;

            //实例化并显示自定义对话框
            QDialog dialog;
            dialog.setWindowTitle("保存成功");
            dialog.setFixedSize(150,50);
            //创建按钮
            QPushButton *btn = new QPushButton("确定", &dialog);

            //创建垂直布局管理器
            QVBoxLayout *layout = new QVBoxLayout(&dialog);
            layout->addWidget(btn, 0, Qt::AlignCenter); //将按钮添加到布局管理器，并设置居中对齐

            //将布局管理器设置为对话框的布局
            dialog.setLayout(layout);

            //显示对话框
            connect(btn, &QPushButton::clicked,&dialog,&QDialog::accept);
            int result = dialog.exec();
            if(result == QDialog::Accepted){
                dialog.close();
            }

            //关闭文件
            file.close();
        }
    });
}

/*void Widget::onSaveButtonClicked()
{
    //获取文件路径
    QString path = ui->lineEdit->text();
    //打开文件进行写入
    QFile file(path);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){ //以写入和文本模式打开文件
        //获取textEdit中的内容
        QString content = ui->textEdit->toPlainText();
        //将内容写入文件
        QTextStream out(&file);
        out << content;
        //关闭文件
        file.close();
    }
}*/

Widget::~Widget()
{
    delete ui;
}
