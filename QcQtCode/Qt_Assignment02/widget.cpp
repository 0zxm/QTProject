#include "widget.h"
#include "ui_widget.h"
#include <QMovie>
#include <QMediaPlayer>
#include <QVideoWidget>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //lable设置背景图片
    QMovie * background = new QMovie(":/new/prefix1/Image/mario.gif");
    ui->label->setMovie(background);
    ui->label->setScaledContents(true); // 将内容缩放以适应控件大小

    background->start();

    background->setSpeed(1000);

    // QMediaPlayer *player = new QMediaPlayer;
    // player->setSource(QUrl::fromLocalFile("path/to/your/mediafile.mp3"));
    // player->play();
}

Widget::~Widget()
{
    delete ui;
}
/*
 * 在Qt中播放视频，您可以使用QMediaPlayer和QVideoWidget类。下面是一个简单的示例，展示如何使用Qt播放视频文件：

首先，在Qt Designer中，拖拽一个QWidget到界面中，并将其布局设置为垂直布局（verticalLayout）。
在这个QWidget中，再次拖拽一个QWidget，并在其上进行右键选择布局，比如水平布局。这样，内部的QWidget就会自适应外部QWidget的大小。
在Qt项目的.pro文件中，添加以下代码：QT += multimedia multimediawidgets。这行代码确保您的项目包含了播放视频所需的模块。
接下来，编辑头文件。您需要包含必要的Qt类头文件，并声明相应的成员变量和函数。
在源文件中，编写代码以设置视频播放器。首先，创建一个QMediaPlayer对象和一个QVideoWidget对象。然后，将QMediaPlayer的视频输出设置到QVideoWidget上。最后，调用QMediaPlayer的play()函数开始播放视频。
完成以上步骤后，您可以编译并运行您的Qt应用程序。如果一切正常，您的应用程序应该能够播放视频文件。
请注意，为了成功播放视频，您的系统需要安装相应的视频解码器。如果没有安装解码器，视频播放可能会失败。在这种情况下，您可以尝试安装一个解码器包，如K-Lite Codec Pack，然后重新构建和运行您的项目。

以上就是在Qt中播放视频的基本步骤。您可以根据自己的需求对项目进行进一步的定制和优化。
 */
