#include "widget.h"

#include <QApplication>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget w;
    w.show();
    return a.exec();
}
