#include <QApplication>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColor>
#include <QIcon>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // // 创建垂直布局
    // QVBoxLayout *verticalLayout = new QVBoxLayout;

    // // 创建水平布局
    // QHBoxLayout *horizontalLayout = new QHBoxLayout;


    QDialog dialog;
    dialog.setWindowIcon(QIcon(":/loveheart"));
    dialog.setFixedSize(350,100);
    dialog.setWindowTitle("表白小程序");

    QLabel *label = new QLabel(&dialog);
    label->setText("你接受我的表白吗"); // 确保文本正确设置
    //label->setStyleSheet("border: 1px solid red; text-align: center;"); // 添加边框和文本居中样式
    label->show();
    label->resize(300,300);
    QPalette palette = label->palette();
    palette.setColor(QPalette::Text, QColor(0, 0, 255)); // 设置文本颜色为蓝色
    label->setPalette(palette);
    label->setGeometry(120, 0,100,50); // 设置位置和大小

    QPushButton *btnYes = new QPushButton("Yes", &dialog);
    QPushButton *btnNo = new QPushButton("No", &dialog);
    btnYes->setGeometry(50, 50, 100, 30);
    btnNo->setGeometry(200, 50, 100, 30);

    // 创建widget
    QWidget *buttonWidget = new QWidget(&dialog);

    // 创建水平布局
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);

    buttonLayout->addWidget(btnYes);
    buttonLayout->addWidget(btnNo);
    buttonWidget->setLayout(buttonLayout);

    // // 创建垂直布局
    // QVBoxLayout *verticalLayout = new QVBoxLayout;

    // // 将标签和widget添加到垂直布局中
    // verticalLayout->addWidget(label);
    // verticalLayout->addWidget(buttonWidget);

    // // 将垂直布局设置为对话框的布局
    // dialog.setLayout(verticalLayout);

    // // 将标签添加到水平布局中
    // horizontalLayout->addWidget(label);

    // // 将水平布局添加到垂直布局中
    // verticalLayout->addLayout(horizontalLayout);

    // // 将垂直布局设置为对话框的布局
    // dialog.setLayout(verticalLayout);


    // 设置父子关系
    btnYes->setParent(&dialog);
    btnNo->setParent(&dialog);

    // 连接按钮的点击事件
    QObject::connect(btnYes, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(btnNo, &QPushButton::clicked, &dialog, &QDialog::reject);
    dialog.setModal(true);//为什么这行不起作用(似乎是模态对话框是针对当前程序而言的,并不能阻止操作系统其他窗口切换)

    // 显示主对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 用户点击了 "Yes" 按钮，退出应用程序
        return 0;
    } else {
        // 用户点击了 "No" 按钮，继续循环
        while (true) {
            QDialog loopDialog;
            loopDialog.setWindowTitle("循环对话框");
            loopDialog.setWindowFlag(Qt::WindowStaysOnTopHint);
            loopDialog.setModal(true);
            loopDialog.setFixedSize(350, 100); // 设置固定大小

            QLabel *label = new QLabel(&loopDialog);
            label->setText("你在考虑下,接不接受"); // 确保文本正确设置
            label->show();
            label->setGeometry(120, 10, 150, 35); // 设置位置和大小
            //label->setStyleSheet("border: 1px solid black"); // 添加边框以显示位置
            QPalette palette = label->palette();
            palette.setColor(QPalette::Text, QColor(0, 0, 255)); // 设置文本颜色为蓝色
            label->setPalette(palette);

            QPushButton *btnYesLoop = new QPushButton("Yes", &loopDialog);
            QPushButton *btnNoLoop = new QPushButton("No", &loopDialog);
            btnYesLoop->setGeometry(50, 50, 100, 30);
            btnNoLoop->setGeometry(200, 50, 100, 30);

            // 设置父子关系
            btnYesLoop->setParent(&loopDialog);
            btnNoLoop->setParent(&loopDialog);

            // 连接按钮的点击事件
            QObject::connect(btnYesLoop, &QPushButton::clicked, &loopDialog, &QDialog::accept);
            QObject::connect(btnNoLoop, &QPushButton::clicked, &loopDialog, &QDialog::reject);

            // 显示循环对话框
            if (loopDialog.exec() == QDialog::Accepted) {
                // 用户点击了 "Yes" 按钮，退出循环
                break;
            }
        }
    }

    // 退出应用程序
    return 0;
}
