#include "dialoglist.h"
#include "ui_dialoglist.h"
#include "widget.h"

DialogList::DialogList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DialogList)
{
    ui->setupUi(this);
    this->setFixedSize(250,700);

    //设置标题
    this->setWindowTitle("MyselfQQ2024");
    //设置图标
    this->setWindowIcon(QPixmap(":/qq/R-C (1).jfif"));

    //文字资源
    QStringList namelist;
    namelist << "斧头帮帮主" <<"飞天魔女"<<"紫衣剑侠"<<"青衫书生"<<"铁血大侠"<<"神医毒手"<<"绝世剑魂" << "乾坤一剑"<<"独孤求败";

    //头像资源
    QStringList profile_photos;
    profile_photos << ":/qq/2019812345950693.jpeg"<<":/qq/20204112252518189.jpg"<<":/qq/OIP-C (3).jfif"<<":/qq/OIP-C (2).jfif";


    QVector<QToolButton*>vToolButton;


    for(int i = 1; i <= 9; i++){
        //设置头像 QToolButton有透明效果
        QToolButton *btn= new QToolButton(this);

        QFont font;
        font.setBold(1);
        font.setFamily("华文新魏");
        font.setPointSize(18);
        btn->setFont(font);

        btn->setText(namelist[i-1]);
        btn->setIcon(QIcon(profile_photos[i%4]));
        btn->setIconSize(QSize(80,80));
        btn->setFixedSize(230,90);
        //设置按钮效果 浮动透明
        btn->setAutoRaise(true);
        //设置风格图标和文字同时显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //把按钮放到垂直布局
        ui->vLayout->addWidget(btn);

        //把按钮放到容器里,方便以后管理
        vToolButton.append(btn);

        //9个窗口标识的初始化
        widgetisShow[i-1] = false;
    }
    //对按钮进行信号槽连接
    for(int i = 0; i < vToolButton.size(); i++){
        connect(vToolButton[i],&QToolButton::clicked,[=](){
            //如果被打开了,就不要再次打开或创建
            if(widgetisShow[i]){
                QMessageBox::warning(this,"警告",QString("%1已经被弹出").arg(vToolButton[i]->text()));
                return;
            }
            widgetisShow[i] = true;
            //弹出聊天对话框
            //构造聊天窗口时告诉窗口名字
            Widget * widget = new Widget(0,vToolButton[i]->text());//0表示以顶层的方式弹出,无父窗口
            //设置窗口标题
            widget->setWindowTitle(vToolButton[i]->text());
            widget->setWindowIcon(vToolButton[i]->icon());
            widget->show();

            connect(widget,&Widget::closeWidget,[=](){
                widgetisShow[i] = false;
            });
        });
    }

}

DialogList::~DialogList()
{
    delete ui;
}
