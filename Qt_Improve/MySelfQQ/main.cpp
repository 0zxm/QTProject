#include "dialoglist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogList l;
    l.show();

    return a.exec();
}
