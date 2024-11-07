#include "widget.h"
#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("表白小程序");
    w.setWindowIcon(QIcon(":/loveheart.jfif"));
    //css样式表
    //w.setStyleSheet("QWidget { background-image: url(:/loveheart.jfif); background-repeat: no-repeat; background-position: center; }");
    w.show();
    return a.exec();
}
