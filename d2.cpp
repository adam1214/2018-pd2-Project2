#include "d2.h"
#include "ui_d2.h"

D2::D2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::D2)
{
    ui->setupUi(this);
}

D2::~D2()
{
    delete ui;
}
