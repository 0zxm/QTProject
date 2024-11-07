
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    // 创建一个人物
    QGraphicsEllipseItem *character = scene.addEllipse(0, 0, 50, 50);
    character->setBrush(Qt::blue);

    // 创建几把飞剑
    const int numSwords = 5;
    QGraphicsEllipseItem *swords[numSwords];
    for (int i = 0; i < numSwords; ++i) {
        swords[i] = scene.addEllipse(0, 0, 20, 100);
        swords[i]->setBrush(Qt::red);
    }

    // 设置飞剑围绕的半径
    const int radius = 100;

    // 创建一个定时器，用于更新飞剑的位置
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        static double angle = 0;
        for (int i = 0; i < numSwords; ++i) {
            double swordAngle = 2 * M_PI / numSwords * i + angle;
            swords[i]->setPos(character->pos().x() + radius * std::cos(swordAngle),
                              character->pos().y() + radius * std::sin(swordAngle));
        }
        angle += 0.1;
        if (angle >= 2 * M_PI) {
            angle = 0;
        }
        view.viewport()->update();
    });
    timer.start(50);


    view.show();

    return a.exec();
}
