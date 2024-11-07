#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //点击文件,弹出对话框
    connect(ui->actionnew, &QAction::triggered,[=](){
        //对话框 分类
        //1.模态对话框(不可以对其他窗口进行操作)
        //2.非模态对话框(可以对其他窗口进行操作)
        //1.模态
        // QDialog dlg(this);
        // dlg.exec();//阻塞
        // dlg.resize(300,200);
        // qDebug() << "模态对话框弹出了";
        // QDialog a(this);
        // a.exec();
        // a.show();

        //2.非模态,不阻塞
        // QDialog dlg2(this);lambda放栈上是临时对象,只会出现闪烁消失的效果
        // dlg2.show();
        // QDialog *dlg2 = new QDialog(this);//放堆上
        // dlg2->resize(300,300);
        // dlg2->show();
        // qDebug() << "非模态对话框弹出了";
        // dlg2->setAttribute(Qt::WA_DeleteOnClose);//55号属性,关闭对话框时析构,防止内存泄漏

        //创建消息对话框
        //1.错误对话框
        //QMessageBox :: critical(this,"critical","错误");
        //2.信息对话框
        //QMessageBox :: information(this,"information","信息");
        //3.提问对话框
        //参数1:父亲 参数2:标题 参数3:提示内容 参数4:按键类型 参数5:默认选中
        //返回值类型
        // if(QMessageBox ::Save == QMessageBox::question(this, "ques","提问", QMessageBox ::Save | QMessageBox ::Cancel, QMessageBox ::Save)){
        //     qDebug() << "选择保存";
        // }else{
        //     qDebug() << "选择取消";
        // }
        //4.警告对话框
        // QMessageBox::warning(this,"warn","警告",QMessageBox::Ok,QMessageBox::Ok);

        //其他标准对话框
        //颜色
        // QColor color = QColorDialog ::getColor(QColor(255,0,0,0));//rgb三原色,a是透明度
        // qDebug() << "r=" << color.red() << "g=" << color.green() << "b=" << color.blue();

        //文件对话框 参数1:父亲  参数2:标题  参数3:默认打开路径  参数4:过滤的文件的格式
        // QString str = QFileDialog :: getOpenFileName(this,"打开文件","C:\\Users\\86158\\Desktop","(*.txt)");
        // qDebug() << str;//返回值是路径
        //字体对话框
        // bool flag;
        // QFont font = QFontDialog ::getFont(&flag,QFont("宋体",36));

        // qDebug() <<"字体类型"<< font.family().toUtf8().data()<<"大小" << font.pointSize()<<"是否加粗" << font.bold()<<"是否倾斜"<< font.italic();

        // // 创建字体对话框
        // QFontDialog fontDialog(font);

        // // 显示字体对话框
        // if (fontDialog.exec()) {
        // // 用户选择了新的字体
        // QFont selectedFont = fontDialog.selectedFont();
        // qDebug() << "选择的字体：" << selectedFont.family() << "大小：" << selectedFont.pointSize();
        // } else {
        // // 用户取消了字体选择
        // qDebug() << "用户取消了字体选择";
        // }


    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
