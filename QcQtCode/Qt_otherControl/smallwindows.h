#ifndef SMALLWINDOWS_H
#define SMALLWINDOWS_H

#include <QWidget>

namespace Ui {
class SmallWindows;
}

class SmallWindows : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWindows(QWidget *parent = nullptr);
    ~SmallWindows();

private:
    Ui::SmallWindows *ui;
};

#endif // SMALLWINDOWS_H
