#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("0zxm的音乐播放器");
    w.show();
    return a.exec();
}
