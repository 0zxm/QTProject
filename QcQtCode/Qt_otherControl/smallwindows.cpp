#include "smallwindows.h"
#include "ui_smallwindows.h"

SmallWindows::SmallWindows(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmallWindows)
{
    ui->setupUi(this);
}

SmallWindows::~SmallWindows()
{
    delete ui;
}
