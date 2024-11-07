/******************************************************************
* @projectName   myTcpserver
* @brief         ldlsrlwidget.cpp
* @author        Li Dongling
* @email         2032323985@qq.com
*******************************************************************/
#include "ldlsrlwidget.h"
#include "ui_ldlsrlwidget.h"

ldlsrlwidget::ldlsrlwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ldlsrlwidget)
{
    ui->setupUi(this);
    /* 摇杆大小输入限制 */
    ui->spinBox->setMinimum(50);
    ui->spinBox->setMaximum(200);
    ui->spinBox->setSingleStep(10);
    /* 死区百分比输入限制 */
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(100);
    ui->spinBox_2->setSingleStep(1);
    /* 灵敏度输入限制 */
    ui->spinBox_3->setMinimum(100);
    ui->spinBox_3->setMaximum(1000);
    ui->spinBox_3->setSingleStep(10);
}

ldlsrlwidget::~ldlsrlwidget()
{
    delete ui;
}
void ldlsrlwidget::getXYsig(int Xsig,int Ysig)//获取摇杆偏移量
{
    QString str;
    str = "X:"+QString::number(Xsig);
    ui->label_2->setText(str);
    str = "Y:"+QString::number(Ysig);
    ui->label_4->setText(str);
}
void ldlsrlwidget::on_pushButton_clicked()//设置摇杆大小
{
    emit set1sig(ui->spinBox->text().toUInt());
}
void ldlsrlwidget::on_pushButton_2_clicked()//设置死区百分比
{
    emit set2sig(ui->spinBox_2->text().toUInt());
}
void ldlsrlwidget::on_pushButton_3_clicked()//灵敏度
{
    emit set3sig(ui->spinBox_3->text().toUInt());
}
