#include "mainscene.h"

#include <QApplication>
#include <QSoundEffect>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    QSoundEffect * mainSound = new QSoundEffect();
    // 设置音效文件路径
    mainSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));//一定要加::fromLocalFile
    mainSound->play();
    w.show();
    return a.exec();
}
