#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("学生管理系统V1.0");
    this->setWindowIcon(QIcon(":/1-titleico.jpg"));

    QString qssTV = "QTableWidget::item:hover{background-color:rgb(92,188,227,200)}"
                    "QTableWidget::item:selected{background-color:#1B89A1}"
                    "QHeaderView::section,QTableCornerButton:section{ \
        padding:3px; margin:0px; color:#DCDCDC;  border:1px solid #242424; \
        border-left-width:0px; border-right-width:1px; border-top-width:0px; border-bottom-width:1px; \
        background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #646464,stop:1 #525252); }"
    "QTableWidget{background-color:white;border:none;}";

    //设置文字对齐
    // ui->tableWidget->setStyleSheet("QTableWidgetItem { text-align: center; }");


    ui->tableWidget->setStyleSheet(qssTV);
    ui->tableWidget->setShowGrid(true); //设置显示格子线
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //行头自适应表格
    ui->tableWidget->horizontalHeader()->setFont(QFont("song", 12));

    // 设置表头为可编辑
    ui->tableWidget->horizontalHeader()->setSectionsMovable(true);
    ui->tableWidget->verticalHeader()->setSectionsMovable(true);
    // ui->tableWidget->horizontalHeader()->setEditTriggers(QAbstractItemView::DoubleClicked); // 仅双击时允许编辑(无效)

    //点击表时不对表头行光亮（获取焦点）
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    //设置表头字体加粗
    QFont font =  ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);

    //所有单元格的字体  设置成一样
    ui->tableWidget->setFont(QFont("song", 12));


    readDataFromFile("D:\\Qt\\QtCode\\QcQtCode\\StuManager\\student.txt");



    /*实现点击排序
    QHeaderView *header = ui->tableWidget->horizontalHeader();
    connect(header, &QHeaderView::sectionClicked, [=](int logicalIndex) {
        // 获取表头视图
        // QHeaderView *header = ui->tableWidget->horizontalHeader();
        // 获取排序状态和顺序
    Qt::SortOrder order = header->sortIndicatorOrder();
        // 如果之前已经排序，则根据当前点击的列进行排序反转
    if (order != Qt::AscendingOrder) {
            order = Qt::AscendingOrder;
        }
        // 设置排序状态和顺序
        this->currentColumn = logicalIndex;
        header->setSortIndicator(currentColumn, order);
        qDebug() << "column:" << currentColumn;
        ui->tableWidget->setSortingEnabled(true);
        header->setSectionsClickable(true);
        // 排序表格数据
        ui->tableWidget->sortItems(currentColumn, order);
    });*/
    QHeaderView *header = ui->tableWidget->horizontalHeader();

    connect(header, &QHeaderView::sectionClicked, [=]() {
        // 获取当前的排序状态和顺序
        qDebug() << "表头被点击了";
        ui->tableWidget->setSortingEnabled(true);
        // header->setSectionsClickable(true);
        Qt::SortOrder currentOrder = header->sortIndicatorOrder();
        qDebug() << currentOrder;
        /*// 切换排序状态
        Qt::SortOrder newOrder = (currentOrder == Qt::DescendingOrder) ? Qt::AscendingOrder : Qt::DescendingOrder ;
        qDebug() << currentOrder;
        qDebug() << newOrder;
        // 设置新的排序状态和顺序
        header->setSortIndicator(logicalIndex, newOrder);
        qDebug() << "column:" << logicalIndex;
        ui->tableWidget->setSortingEnabled(true);
        header->setSectionsClickable(true);
        // 排序表格数据
        ui->tableWidget->sortItems(logicalIndex, newOrder);*/
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::readDataFromFile(const QString& filename){
    //打开文件
    QFile file(filename);
    //判断文件是否打开成功
    if(!file.open(QIODevice::ReadOnly)){
        qInfo() << filename << "打开失败";
    }else{
        qInfo() << "打开成功";
    }
    //读取文件
    QTextStream stream(&file);
    /*//创建一个模型
    QStandardItemModel *model = new QStandardItemModel(this);
    //把模型交给视图
    ui->tableWidget->setModel(model);*/
    //1.表头
    QStringList headers = stream.readLine().split(",");
    qDebug() << headers.size();

    ui->tableWidget->setColumnCount(headers.size());//你不先创建列,表头显示不出来

    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setVisible(true);

    //2.数据
    while(!stream.atEnd()){
        QStringList line_data = stream.readLine().split(",");
        qDebug() << line_data;
        //生成元素项
        int row = ui->tableWidget->rowCount();  // 获取当前行数
        ui->tableWidget->insertRow(row);  // 插入新行
        for (int column = 0; column < line_data.size(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(line_data.at(column));
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, column, newItem);  // 设置单元格的内容
        }
    }

    file.close();
}
void Widget::closeEvent(QCloseEvent *event) {
    if (!this->isSave) {
        // 弹出提示框
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "app", "是否保存", QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

        if (resBtn == QMessageBox::Yes) {
            // 执行保存操作
            this->saveDataToFile("D:\\Qt\\QtCode\\QcQtCode\\StuManager\\student.txt");
        } else if (resBtn == QMessageBox::No) {
            // 不保存，直接关闭窗口
            // 不需要执行任何操作，事件会自动被接受，即关闭窗口
            event->accept();
        } else {
            // 取消关闭操作
            event->ignore();
        }
    } else {
        // 没有需要保存的数据，直接关闭窗口
        // 不需要执行任何操作，事件会自动被接受，即关闭窗口
    }
}

void Widget::on_pushButton_3_clicked()
{
    // 添加学生
    // 给表格添加空行
    int row = ui->tableWidget->rowCount();  // 获取当前行数
    qInfo() << row;

    ui->tableWidget->insertRow(row);  // 插入新行

    // 把表格滚动到最下面
    ui->tableWidget->scrollToBottom();

    // 手动排序新添加的行
    for (int col = 0; col < ui->tableWidget->columnCount(); col++) {
        QTableWidgetItem *item = new QTableWidgetItem("");
        item->setTextAlignment(Qt::AlignCenter);  // 设置文本居中对齐
        ui->tableWidget->setItem(row, col, item);
    }

    // 重新排序表格数据
    // ui->tableWidget->sortItems(ui->tableWidget->horizontalHeader()->sortIndicatorSection(),ui->tableWidget->horizontalHeader()->sortIndicatorOrder());

    this->isSave = false;
}


void Widget::on_pushButton_2_clicked()
{
    saveDataToFile("D:\\Qt\\QtCode\\QcQtCode\\StuManager\\student.txt");
    this->isSave = true;

}

        void Widget::saveDataToFile(const QString &filename) {
        // 保存学生
        // 1.打开文件
        QFile file("D:\\Qt\\QtCode\\QcQtCode\\StuManager\\student.txt");
        // 判断文件是否打开成功
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            qInfo() << filename << "打开失败";
        } else {
            qInfo() << "打开成功";
            // 2.获取表头标题
            QString headers;
            int column = ui->tableWidget->columnCount();
            for (int i = 0; i < column; i++) {
                QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(i);
                if (item) {
                    headers += item->text();
                    if (i != column - 1) {
                        headers += ",";
                    } else {
                        headers += "\n";
                    }
                } else {
                    QMessageBox::information(this, "信息", "表头保存失败，请检查", QMessageBox::Close);
                    return;
                }
            }
            QTextStream stream(&file);
            stream << headers;
            // 3.保存数据
            for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
                QString lineData;
                bool hasEmptyItem = false;  // 用于标记是否存在空项
                for (int j = 0; j < column; j++) {
                    QTableWidgetItem *item = ui->tableWidget->item(i, j);
                    if (item!=nullptr && item->text()!="") {
                        lineData.push_back(item->text());
                        if (j != column - 1) {
                            lineData.push_back(",");
                        } else {
                            lineData.push_back("\n");
                        }
                    } else {
                        hasEmptyItem = true;  // 标记存在空项
                        break;  // 跳出当前循环
                    }
                }
                if (!hasEmptyItem) {  // 如果此项非空才写入文件
                    stream << lineData;
                }
            }
            file.close();  // 关闭文件
    }
}



void Widget::on_pushButton_clicked()
{
    //删除学生
    int current_row = ui->tableWidget->currentRow();

    ui->tableWidget->removeRow(current_row);

    this->isSave=false;


}

void Widget::on_tableWidget_itemDoubleClicked(QTableWidgetItem *)
{
    this->isSave = false;
}

