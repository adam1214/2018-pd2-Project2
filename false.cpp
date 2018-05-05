#include "false.h"
#include "ui_false.h"

False::False(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::False)
{
    ui->setupUi(this);
}

False::~False()
{
    delete ui;
}
