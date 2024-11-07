#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("马里奥速通");
    w.setWindowIcon(QIcon(":/new/prefix1/Image/OnePiece.png"));
    w.show();
    return a.exec();
}
