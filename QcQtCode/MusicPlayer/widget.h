#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidgetItem>
#include <QWidget>
#include <QMediaPlayer>//播放音乐
#include <QAudioOutput>//输出声音
#include <QMouseEvent>
#include <QMenu>

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

private slots:
    void on_pushButton_file_name_clicked();

    void on_pushButton_file_play_clicked();

    void on_pushButton_file_last_clicked();

    void on_pushButton_file_next_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void paintEvent(QPaintEvent *);

    void on_pushButton_file_volume_clicked();


private:
    Ui::Widget *ui;

    QAudioOutput * audioOutput;
    QMediaPlayer * mediaPlayer;
    int currentIndex = 0;//当前选中歌曲

    QList<QUrl> playList;
signals:


};
#endif // WIDGET_H
