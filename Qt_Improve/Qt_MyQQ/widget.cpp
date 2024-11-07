#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始化ui界面
    initWidgetUi();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidgetUi(){

    //按钮
    ui->pushButton_cls->setText("清屏");
    ui->pushButton_bold->setText("加粗");
    ui->pushButton_italic->setText("斜体");
    ui->pushButton_color->setText("颜色");
    ui->pushButton_save->setText("保存");
    ui->pushButton_send->setText("发送");
    ui->pushButton_underline->setText("下划线");

    //下拉框
    ui->comboBox_font->setCurrentText("字体");
    ui->comboBox_font->addItem("字体");
    ui->comboBox_size->setCurrentText("大小");
    ui->comboBox_size->addItem("大小");

    ui->comboBox_size->addItem("16");
    ui->comboBox_size->addItem("18");
    ui->comboBox_size->addItem("20");
    ui->comboBox_size->addItem("22");
    ui->comboBox_size->addItem("24");
    ui->comboBox_size->addItem("26");
    ui->comboBox_size->setCurrentIndex(0);



}

void Widget::on_pushButton_color_clicked()
{
    color = QColorDialog::getColor(color,this);

    if(color.isValid()){
        ui->textEdit_msg->setTextColor(color);
        ui->textEdit_msg->setFocus();
    }
}


void Widget::on_pushButton_quit_clicked()
{
    this->close();
}



void Widget::on_pushButton_bold_clicked(bool checked)
{
    if(checked){
        ui->textEdit_msg->setFontWeight(QFont::Bold);
    }else{
        ui->textEdit_msg->setFontWeight(QFont::Normal);
    }
    ui->textEdit_msg->setFocus();
}


void Widget::on_pushButton_italic_clicked()
{
    ui->textEdit_msg->setFontItalic(true);
    ui->textEdit_msg->setFocus();
}


void Widget::on_pushButton_underline_clicked()
{
    ui->textEdit_msg->setFontUnderline(true);
    ui->textEdit_msg->setFocus();
}


void Widget::on_comboBox_size_currentIndexChanged(int index)
{
    int size = ui->comboBox_size->itemText(index).toInt();
    qDebug() << size;
    ui->textEdit_msg->setFontPointSize(size);
}


void Widget::on_pushButton_send_clicked()
{
    if(ui->tableWidget_userlist->selectedItems().isEmpty()){
        QMessageBox::warning(0,"选择","请选择要发送的目标用户!",QMessageBox::Ok);
        return;
    }

}

