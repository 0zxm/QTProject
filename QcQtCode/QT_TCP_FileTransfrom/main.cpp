#include "server.h"
#include "clientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.show();
    ClientWidget c;
    c.show();
    return a.exec();
}
