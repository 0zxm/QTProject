#include "studentdlg.h"
#include "ui_studentdlg.h"

StudentDlg::StudentDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentDlg)
{
    ui->setupUi(this);

    setFixedSize(this->width(),this->height());

    // 调用函数创建且打开数据库
    CreateDatabaseFunc();

    // 调用函数创建数据表
    CreateTableFunc();

    // 执行查询操作(初始化列表)
    QueryTableFunc();

    /*// 连接信号和槽以在用户点击表头时排序
    connect(ui->tableView, &QTableView::sortByColumn, [=](int column) {
        sqlmodel.sort(column); // 根据指定的列进行排序
});*/

    //下拉菜单的实现
    ui->comboBoxCond_sort->addItem("升序");
    ui->comboBoxCond_sort->addItem("降序");
    ui->comboBoxCond_sort->addItem("默认");
}

StudentDlg::~StudentDlg()
{
    sqldb.close(); // 在析构函数中关闭数据库连接
    delete ui;
}

void StudentDlg::CreateDatabaseFunc()  //    创建SQLite数据库
{
    // 1：添加数据库驱动
    sqldb=QSqlDatabase::addDatabase("QSQLITE");

    // 2：设置数据库名称
    sqldb.setDatabaseName("studentmis.db");

    bool isOpen = sqldb.open();
    // 3：打开此数据库是否成功
    if(isOpen)
    {
        QMessageBox::information(0,"正确","恭喜你，数据库打开成功！",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(0,"错误","数据库打开失败，请重新检测！",QMessageBox::Ok);
    }
}

void StudentDlg::CreateTableFunc()     // 创建SQLite数据表
{
    QSqlQuery createquery;

    // 创建SQL语句
    QString strsql=QString("create table student("
                           "id text primary key not null,"
                           "name text not null,"
                           "score real not null);");

    // 执行SQL语句
    if(createquery.exec(strsql)==false)
    {
        QMessageBox::critical(0,"失败","student数据表创建失败，请重新检查！",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(0,"成功","恭喜你，student数据表创建成功！",QMessageBox::Ok);
    }



}
void StudentDlg::QueryTableFunc()      // 执行查询操作
{

    QString sql_cmd = "select * from student";
    sqlmodel.setQuery(sql_cmd);
    sqlmodel.setHeaderData(0,Qt::Horizontal,"学号(唯一)");
    sqlmodel.setHeaderData(1,Qt::Horizontal,"姓名");
    sqlmodel.setHeaderData(2,Qt::Horizontal,"综合评分");
    ui->tableView->setModel(&sqlmodel);
}

void StudentDlg::on_pushButtonSort_clicked()
{
    /*QString strCondition="ASC"; // 默认按升序排序
    QString strSQL=QString("select * from student order by %1").arg(strCondition);
    sqlmodel.setQuery(strSQL);
    if(!sqlmodel.query().exec()) {
        qDebug() << "排序失败";
    }
    ui->tableView->setModel(&sqlmodel);
    QueryTableFunc();

    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(2,Qt::DescendingOrder);
    sqlmodel.sort(2,Qt::DescendingOrder);
    ui->tableView->setModel(&sqlmodel);
    QString strSQL=QString("select * from student order by column_name DESC");
    sqlmodel.setQuery(strSQL);
    QueryTableFunc();
    ui->tableView->repaint();*/

    // 获取排序下拉框中用户的选择
    // QString sortDirection = ui->comboBoxCond_sort->currentText();

    int index = ui->comboBoxCond_sort->currentIndex();

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(&sqlmodel);

    // 接下来，您可以设置排序的列和顺序
    if(index == 0){
        proxyModel->sort(2, Qt::AscendingOrder);
    }else if(index == 1){
        proxyModel->sort(2, Qt::DescendingOrder); // columnIndex 是您想要排序的列的索引
    }else{
        proxyModel->sort(-1);
    }
    // 现在，proxyModel 包含了排序后的数据，您可以将其设置为视图（如 QTableView）的模型
    ui->tableView->setModel(proxyModel);
}

void StudentDlg::on_pushButton_INSERT_clicked()
{
    QSqlQuery sqlquery;
    QString id = ui->lineEdit_ID->text();
    if(id=="0000"||id=="")
    {
        QMessageBox::critical(this,"失败","提示：输入错误？学号不能为0000？",QMessageBox::Ok);
        return ;
    }

    QString name=ui->lineEdit_NAME->text();
    if(name=="")
    {
        QMessageBox::critical(this,"失败","提示：输入错误？姓名不能为空？",QMessageBox::Ok);
        return ;
    }

    double score=ui->lineEdit_SCORE->text().toDouble();
    if(score<0 || score>100)
    {
        QMessageBox::critical(this,"失败","提示：输入错误？分数范围(0-100)？",QMessageBox::Ok);
        return ;
    }

    QString strs=QString("insert into student "
                         "values('%1','%2',%3)").arg(id).arg(name).arg(score);

    if(sqlquery.exec(strs)==false)
    {
        QMessageBox::critical(0,"失败","向数据表插入记录失败，请重新检查！",QMessageBox::Ok);
        return;
    }
    else
    {
        QMessageBox::information(0,"成功","恭喜你，向数据表插入记录成功！",QMessageBox::Ok);
        //更新数据
        QueryTableFunc();

    }

}

void StudentDlg::on_pushButton_DELETE_clicked()
{
    QSqlQuery query;
    QString id = currentIndexModel.siblingAtColumn(0).data().toString();
    QString sql = QString("delete from student where id='"+id+"';"); // 使用arg()函数来添加id
    query.prepare(sql); // 准备SQL查询
    bool ok = query.exec(sql); // 执行查询  prepare()函数来准备SQL查询。在执行查询之前准备查询可以提高性能，并确保只有在查询准备好之后才执行它
    if(ok){
        qDebug() << "成功";
    }else{
        qDebug() << "失败";
        return;
    }
    if(this->scence == 1){
        QueryTableFunc();
    }
    QMessageBox::about(this,"消息","删除成功");
}

void StudentDlg::on_pushButton_UPDATE_clicked()
{
    QSqlQuery query;
    QString id = ui->lineEdit_ID->text();
    QString name = ui->lineEdit_NAME->text();
    int score = ui->lineEdit_SCORE->text().toInt();
    QString sql = ("UPDATE student SET name = '" + name + "', score = " + QString::number(score) + " WHERE id = '" + id + "'"); // 更新修改信息
    query.exec(sql); // 执行查询
    QMessageBox::about(this, "消息", "修改成功");
    QueryTableFunc();
}

void StudentDlg::on_pushButton_SEARCH_clicked()
{
    QSqlQuery query;
    QString id = ui->lineEdit_ID->text();
    // QString name = ui->lineEdit_NAME->text();
    // int score = ui->lineEdit_SCORE->text().toInt();
    if(id!=""){
        QString sql = "SELECT * FROM student WHERE id = '"+id+"';";
        query.exec(sql);
        sqlmodel.setQuery(sql);
        QPushButton * backBtn = new QPushButton(this);
        backBtn->setText("返回");
        backBtn->setGeometry(90,15,50,20);
        backBtn->show();
        connect(backBtn,&QPushButton::clicked,[=](){
            sqlmodel.setQuery("select * from student");
            backBtn->hide();
        });

    }
}

void StudentDlg::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_ID->setText(index.siblingAtColumn(0).data().toString());
    ui->lineEdit_NAME->setText(index.siblingAtColumn(1).data().toString());
    ui->lineEdit_SCORE->setText(QString::number(index.siblingAtColumn(2).data().toInt()));
    currentIndexModel = index;
}

