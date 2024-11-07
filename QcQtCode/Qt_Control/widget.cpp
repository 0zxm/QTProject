#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QListWidget>
#include <qstringlist.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置默认按钮
    ui->rBtnMan->setChecked(1);
    ui->rBtnMarried->setChecked(1);

    //设置是否能被选中
    ui->rBtnMan->setCheckable(1);
    ui->rBtnMarried->setCheckable(0);

    //选中女后,打印信息
    //mutable关键字，这使得lambda函数可以修改male变量。但是，当你从lambda函数外部访问male变量时，它仍然保持其初始值(即false)
    //bool localMale;

    connect(ui->rBtnWoman, &QRadioButton::clicked, [&]() {
        //localMale = true;
        qDebug() << "选中女";
});

    //qDebug() << localMale; // 这将打印true，如果rBtnWoman已经被点击过

    //多选按钮  接收函数int state返回值, 2选中, 0未选, 1半选
    connect(ui->cBox1,&QCheckBox::stateChanged,[=](int state){
        qDebug() << state;
    });

    // //利用listwidget写诗
    // QListWidgetItem * item = new QListWidgetItem("会挽雕弓如满月");
    // //放入listitem
    // ui->listWidget->addItem(item);
    // //设置对其格式
    // item->setTextAlignment(Qt::AlignHCenter);

    //QStringList ~~ List<string>
    QStringList list;
    list << "会挽雕弓如满月" << "西北望射天狼";
    ui->listWidget->addItems(list);

}

Widget::~Widget()
{
    delete ui;
}
