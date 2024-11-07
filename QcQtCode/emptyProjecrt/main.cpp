#include <QApplication>
#include <QtWidgets>
#include <QDebug>
int main(int argc, char* argv[]){
    QApplication a(argc,argv);

    QTabWidget w;

    w.show();
    //Qt文件名和类名是一致的

    qDebug() << "hello world";
    //a.exec();
    return a.exec();
}
