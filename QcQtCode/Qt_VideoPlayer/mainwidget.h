#ifndef WIDGET_H
#define WIDGET_H

#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QMediaPlayer>
// #include <QMediaPlaylist>
#include <QVideoWidget>
#include <QGraphicsVideoItem>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QMediaPlayer * player;
    QGraphicsVideoItem * videoitem;
    QString durationtime,positiontime;

private slots:
    void onStateChanged(QMediaPlayer::PlaybackState state);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 positiontime);


    void on_open_pushButton_clicked();
    void on_pushButton_play_clicked();
    void on_pushButton_pause_clicked();
    void on_pushButton_slient_clicked();
};
#endif // WIDGET_H
