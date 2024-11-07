#include "mylistwidget.h"

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget{parent}
{

}

//重写菜单事件
void MyListWidget::contextMenuEvent(QContextMenuEvent *event){
// 检查是否点击了某个 item
    QListWidgetItem *item = itemAt(event->pos());
    if (item) {
        QMenu contextMenu;
        // 添加你的上下文菜单项
        contextMenu.addAction("删除");
        // 显示上下文菜单
        QAction *action = contextMenu.exec(event->globalPos());
        if (action && action->text() == "删除") {
            // 如果用户选择了“删除”，则删除该项
            emit reMove(item);
            // int row = row(item); // 获取项目的行号
            // int index = indexOf(item); // 获取项目的索引
            // delete takeItem(index); // 从列表中移除项目
            // // 如果需要，可以触发信号更新视图
            // emit itemRemoved(row);
        }
    }else {
        // 如果不是点击的 item，则调用基类的默认实现
        QListWidget::contextMenuEvent(event);
    };
}
