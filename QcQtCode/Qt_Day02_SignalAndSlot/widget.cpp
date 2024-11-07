#include "widget.h"
#include "ui_widget.h"


//Teacher 类 老师类
//student类 学生类
//下课后，老师会触发一个信号，饿了 ，学生响应信号，请客吃饭
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->resize(600,200);
    //创建一个老师对象
    this->t = new Teacher(this);

    //创建一个学生对象
    this->s = new Student(this);

    //connect
    //connect(t, &Teacher :: hungry, s, &Student :: treat);

    //链接有参
    //地址指向地址
    //函数指针->函数地址
    // void(Teacher :: *teacherSignal)(QString, int) = &Teacher::hungry;
    // void(Student :: *studentSlot)(QString) = &Student::treat;
    // connect(t, teacherSignal, s, studentSlot);

    //调用下课函数
    classOver();

    //点击一个下课按钮在下课
    QPushButton *btn = new QPushButton("下课",this);
    //重置大小
    this->resize(600,300);

    //点击按钮,触发下课
    //connect(btn,&QPushButton :: clicked,this,&Widget :: classOver);

    //无参信号和槽连接
    void(Teacher :: *teacherSignal2)(void) = &Teacher::hungry;
    void(Student :: *studentSlot2)(void) = &Student::treat;
    connect(t, teacherSignal2, s, studentSlot2);

    //信号连接信号
    connect(btn, &QPushButton::clicked, t, teacherSignal2);

    //断开连接
    //disconnect(btn, &QPushButton::clicked, t, teacherSignal2);

    //拓展
    //1.信号可以连接信号
    //2.一对多或者多对一
    //3.信号和槽的参数 类型必须要一一对应
    //4.信号的参数个数是不是要对应, 信号的参数个数可以多于槽函数
    connect(btn, &QPushButton::clicked,this, &Widget :: classOver);

    //Qt4版本以前的信号和槽的连接方式
    connect(t, teacherSignal2, s, studentSlot2);
    //利用Qt4信号槽,链接无参版本
    //Qt4版本 底层SIGNAL("hungry") SLOT("treat")
    //connect(t,SIGNAL(hungry()), s, SLOT(treat()));
    //Qt4版本优点:参数直观，缺点: 类型不做检测,编译不会报错,运行会错,Qt5以上支持Qt4的版本写法

    //lambda表达式
    //[变量传递](){};函数声明 [](){}();函数调用//=值传递,让编译器认识局部变量,&引用传递,让编译器认识局部变量
    //在第一个 connect 函数中，使用了Lambda表达式，并且在Lambda函数内部使用了 mutable 关键字。这允许你在Lambda函数内部修改 m 的值。
    //在第二个 connect 函数中，使用了 = 捕获方式来捕获 m 的值。这意味着在Lambda函数内部不能修改 m 的值,只修改拷贝。
    // QPushButton *btn2 = new QPushButton("下课",this);
    // [btn,btn2](){
    //     btn->setText("aaaa");
    //     btn2->setText("aaaabbbb");
    // }();


    //mutable关键字 用于修饰值传递的变量，修改的是拷贝，而不是本体
    // QPushButton *myBtn = new QPushButton(this);
    // QPushButton *myBtn2 = new QPushButton(this);
    // myBtn->setText("myBtn");
    // myBtn2->setText("myBtn2");
    // myBtn->move(400, 100);
    // myBtn2->move(500, 100);
    // int m = 10;

    // connect(myBtn, &QPushButton::clicked, this, [m]() mutable {
    //     m = 100 + 10;
    //     qDebug() << m;
    // });

    // connect(myBtn2, &QPushButton::clicked, this, [=]() {
    //     qDebug() << m;
    // });

    // qDebug() << m;

    int ret = []()->int{return 100;}();
    qDebug() << "ret=" << ret;

    //利用lambda表达式实现点击关闭窗口
    QPushButton  *btn3 = new QPushButton("关闭",this);
    btn3->move(100,0);

    //connect(btn3,&QPushButton::clicked,this,&Widget::close);
    connect(btn3, &QPushButton::clicked, this, [=](){
        emit s->treat("辣子鸡");
        this->close();
    });
}


// void Widget :: print(){
//     qDebug()<< "结束" ;
// }

void Widget :: classOver(){
    //下课后调用,触发老师饿了的信号
    //emit t->hungry(); //触发emit
    QString str = "辣子鸡";
    emit s->treat(str);
    //emit this->print();
}

Widget::~Widget()
{
    delete ui;
}
