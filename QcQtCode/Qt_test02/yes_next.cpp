#include "yes_next.h"
#include "ui_yes_next.h"

Yes_Next::Yes_Next(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Yes_Next)
{
    ui->setupUi(this);
    this->setWindowTitle("poems");

    /*使用HTML标记：你可以使用HTML标记来在QLabel中显示换行文字。例如，你可以使用<br>标记来表示换行。示例代码如下：
        ui->label->setText("第一行文字<br>第二行文字");
    使用QLabel的setWordWrap方法：你可以使用setWordWrap方法来启用QLabel的自动换行功能。示例代码如下：
        ui->label->setText("这是一段很长的文字，当文字超出label的大小时会自动换行");
        ui->label->setWordWrap(true);
    这两种方法都可以用来在QLabel中显示换行文字。你可以根据你的需求选择其中一种方法*/

    //str.insert(str.indexOf(",") + 1, "&nbsp;");//添加空格

    QString poem = "<br>莎士比亚的《十四行诗》：<br>“我能否将你比作夏日？<br>但你比夏日更可爱也更温柔。”<br>"
                   "<br>杰拉尔德的《未与你共度一切》：<br>“我曾遇到过无数生灵，曾看过无数美景，<br>这一切却未与你共度，<br>这都会是我的损失；<br>这些事情我都想与你共度，"
                   "<br>这一切才会是我的收获。”<br><br>波伏娃的《越洋情书》：<br>“唯有你也想见我的时候，我们的见面才有意义。”<br><br>“犹如飞蛾扑向星星，又如黑夜追求黎明。”<br><br>“见你第一眼我就沦陷了。”<br><br>“他是我的南北，"
                   "我的西东，我的工作日，我的礼拜天，我的正午，我的深夜，我的言语，我的歌声。我认为爱可以不朽。”";

    ui->label->setText(poem);
    ui->label->setStyleSheet("background-color: pink; font-style: italic; font-family: 华文楷体;");
    QFont font = ui->label->font(); // 获取label的当前字体
    font.setPointSize(16); // 设置字体大小为16
    ui->label->setFont(font); // 应用新的字体
    ui->label->setWordWrap(true);

    // 设置背景图片
    QString imagePath = "url(:/loveheart.jfif)"; // 替换成你的图片路径
    this->setStyleSheet("background-image: "+ imagePath + "; background-position: center; background-attachment: fixed;");
    /*使用background-size属性来指定背景图片的大小和填充方式。例如，你可以设置为background-size: cover;
     * 来让背景图片覆盖整个窗口，或者设置为background-size: contain;来让背景图片完整显示在窗口内，不进行裁剪。*/
    //background-repeat: no-repeat不重复

    // // 获取并输出窗口的大小
    // int windowWidth = this->width();
    // int windowHeight = this->height();
    // qDebug() << "窗口宽度：" << windowWidth;
    // qDebug() << "窗口高度：" << windowHeight;
}


Yes_Next::~Yes_Next()
{
    delete ui;
}
