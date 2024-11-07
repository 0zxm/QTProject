#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmallWidget)
{
    ui->setupUi(this);

    //QSpinbox移动,QSlider跟着移动
    void (QSpinBox :: *signal)(int) = &QSpinBox::valueChanged;//函数指针(因为函数有重载)
    connect(ui->spinBox, signal, ui->horizontalSlider, &QSlider::setValue);

    //QSlider滑动,QSpinbox改变
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
}

//设置数值
void SmallWidget :: setNumber(int num){
    ui->spinBox->setValue(num);
}

//获取数值
int SmallWidget :: getNumber(){
    return ui->spinBox->value();
}

SmallWidget::~SmallWidget()
{
    delete ui;
}
