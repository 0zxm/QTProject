#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <QListWidgetItem>
#include <QChar>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushButton_file_name->setIcon(QIcon(":/music_player/equalizer-2935455_640.png"));
    ui->pushButton_file_name->setIconSize(QSize(41,41));

    ui->pushButton_file_last->setIcon(QIcon(":/music_player/advance-2935453_640.png"));
    ui->pushButton_file_last->setIconSize(QSize(41,41));

    ui->pushButton_file_play->setIcon(QIcon(":/music_player/play-2935460_640.png"));
    ui->pushButton_file_play->setIconSize(QSize(41,41));

    ui->pushButton_file_next->setIcon(QIcon(":/music_player/advance-2935453_640_1.png"));
    ui->pushButton_file_next->setIconSize(QSize(41,41));

    ui->pushButton_file_volume->setIcon(QIcon(":/music_player/sound-2935466_640.png"));
    ui->pushButton_file_volume->setIconSize(QSize(41,41));

    ui->playCourseSlider->setStyleSheet("QSlider::handle:horizontal {width: 10px;}");

    //如何播放音乐
    //先new一个output对象
    audioOutput = new QAudioOutput(this);
    //再来一个媒体播放对象
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setLoops(-1);

    // //给播放器设置资源
    // mediaPlayer->setSource(QUrl::fromLocalFile("D:\\CloudMusic\\3305029609.mp3"));
    // //播放
    // mediaPlayer->play();

    // 获取当前媒体的时长,通过信号和槽来获取
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration){
        ui->total_label->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));//参数(数字,固定长度,基数/进制数,填充符)
        ui->playCourseSlider->setRange(0,duration);//设置进度条范围
    });

    //获取当前播放时长
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 pos){
        ui->current_label->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));//参数(数字,固定长度,基数/进制数,填充符)
        ui->playCourseSlider->setValue(pos);
    });
    //拖动进度滑块让音乐改变
    connect(ui->playCourseSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);

    //设置音量改变
    //拖动进度滑块让音乐改变
    // audioOutput->setVolume(1);//[0,1]
    ui->volume_slider->setRange(0,100);
    ui->volume_slider->setSliderPosition(100);
    connect(ui->volume_slider,&QSlider::sliderMoved,audioOutput,[=](int position){
        audioOutput->setVolume(position / 100.0);
    });


    ui->listWidget->setAttribute(Qt::WA_TranslucentBackground);
    // ui->listWidget-> setOpacity(0.5);

    connect(ui->listWidget,&MyListWidget::reMove,this,[=](QListWidgetItem * item){
        int row = ui->listWidget->row(item); // 获取项目的行号
        qDebug() << row;
        // // 获取item对应的QModelIndex
        // QModelIndex modelIndex = ui->listWidget->indexFromItem(item);

        // // 从QModelIndex中获取行号
        // int index = modelIndex.row();
        // qDebug() << index;
        playList.removeAt(row);
        QListWidgetItem *delItem = ui->listWidget->takeItem(row);
        if (delItem) {
            delete delItem; // 释放内存
        }
        ui->listWidget->update();
    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_file_name_clicked()
{
    qInfo()<< "点击打开文件";
    //打开文件对话框
    auto path = QFileDialog::getExistingDirectory(this,"请选择音乐所在的目录","D:\\");//父对象,标题,默认文件夹

    //获取里面所有mp3和wav后缀的文件路径
    QDir dir(path);
    auto musicList = dir.entryList(QStringList()<<"*.mp3" << "*.wav");
    //把音乐名字放到listWidegt
    ui->listWidget->addItems(musicList);
    //默认选中第一个文件
    ui->listWidget->setCurrentRow(0);
    //把音乐的完整路径保存下来
    for(auto file : musicList)
        playList.append(QUrl::fromLocalFile(path +"\\" + file));
    qInfo()<<playList;



}


void Widget::on_pushButton_file_play_clicked()
{
    if(playList.isEmpty()){//错误处理
        return;//防止未选文件就点击播放
    }
    switch(mediaPlayer->playbackState()){
    case QMediaPlayer::PlaybackState::PlayingState: //播放状态
        mediaPlayer->pause();
        ui->pushButton_file_play->setIcon(QIcon(":/music_player/play-2935460_640.png"));
        break;
    case QMediaPlayer::PlaybackState::PausedState:  //暂停状态
        ui->pushButton_file_play->setIcon(QIcon(":/music_player/pause-2935459_640.png"));
        mediaPlayer->play();
        break;
    case QMediaPlayer::PlaybackState::StoppedState: //未播放
    {
        // 检查是否选择了文件夹
        if (ui->listWidget->count() == 0) {
            qDebug() << "没有选择任何文件夹";
            return; // 提前返回，不执行后续的播放逻辑
        }

        // 获取当前选中行号
        currentIndex = ui->listWidget->currentRow();
        if (currentIndex == -1) { // 判断是否选中了任何项
            qDebug() << "没有选中任何音乐文件";
            return; // 提前返回，不执行后续的播放逻辑
        } else{
            mediaPlayer->setSource(playList[currentIndex]);
            ui->pushButton_file_play->setIcon(QIcon(":/music_player/pause-2935459_640.png"));
            mediaPlayer->play();
            break;
        }
    }

    }

}



//上一曲
void Widget::on_pushButton_file_last_clicked()
{

    if(playList.isEmpty()){//错误处理
        return;//防止未选文件就点击播放
    }
    if(currentIndex == 0){
        currentIndex = playList.size()-1;
    }else{
        currentIndex = (currentIndex - 1) % playList.size();
    }
    // qDebug() << currentIndex;
    ui->listWidget->setCurrentRow(currentIndex);
    mediaPlayer->setSource(playList[currentIndex]);
    mediaPlayer->play();
}

//下一曲
void Widget::on_pushButton_file_next_clicked()
{
    if(playList.isEmpty()){//错误处理
        return;//防止未选文件就点击播放
    }
    //让listwidget选中下一行
    // currentIndex++;//会下标越界吗
    // if(currentIndex >= playList.size()){
    //     currentIndex = 0;
    // }
    currentIndex = (currentIndex + 1) % playList.size();
    ui->listWidget->setCurrentRow(currentIndex);
    mediaPlayer->setSource(playList[currentIndex]);
    mediaPlayer->play();



}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    // 获取item对应的QModelIndex
    QModelIndex modelIndex = ui->listWidget->indexFromItem(item);

    // 从QModelIndex中获取行号
    int index = modelIndex.row();
    ui->listWidget->setCurrentRow(index);
    mediaPlayer->setSource(playList[index]);
    mediaPlayer->play();
    this->currentIndex = index;


    //     // 1. 获取被双击项目的文本
    // QString itemText = item->text();

    //     // 2. 打印或显示文本
    // qDebug() << "Double-clicked item text:" << itemText;

    //     // 3. 更多的逻辑可以在这里添加
}
void Widget::paintEvent(QPaintEvent *){
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/music_player/OIP-C.png");
    painter.drawPixmap(0, 0, this->width(), this->height(),pix); //按大小拉伸

    QPainter painter2(ui->listWidget);
    pix.load(":/music_player/smallwidget.png");
    painter2.drawPixmap(10,10,pix.width(),pix.height(),pix);
}

void Widget::on_pushButton_file_volume_clicked()
{
    if(audioOutput->volume() != 0){
        audioOutput->setVolume(0);
        ui->pushButton_file_volume->setIcon(QIcon(":/music_player/sound-2935467_640.png"));
        ui->volume_slider->setSliderPosition(0);
    }else{
        audioOutput->setVolume(1);
        ui->pushButton_file_volume->setIcon(QIcon(":/music_player/sound-2935466_640.png"));
        ui->volume_slider->setSliderPosition(100);
    }

}


// void Widget::mousePressEvent(QMouseEvent * e){
//     if (e->button() == Qt::RightButton) {
//             QMenu contextMenu;
//             contextMenu.addAction("选项1");
//             contextMenu.addAction("选项2");
//             contextMenu.show();
//             contextMenu.exec(e->globalPos()); // 显示菜单并执行相应操作
//         } else {
//             // 调用基类的事件处理器（可选）
//             QWidget::mousePressEvent(e);
//         }
// }

