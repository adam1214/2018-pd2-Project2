#include "true.h"
#include "ui_true.h"

True::True(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::True)
{
    ui->setupUi(this);
}

True::~True()
{
    delete ui;
}
