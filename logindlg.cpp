#include "logindlg.h"
#include "ui_logindlg.h"
#include<QDebug>
LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_pushButton_2_clicked()
{
    //qDebug() << "Generate puzzle randomly";
}

void LoginDlg::on_pushButton_clicked()
{
    //qDebug() << "Set puzzle by you";
}
