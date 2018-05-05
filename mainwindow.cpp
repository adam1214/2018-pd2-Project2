#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "d3.h"
#include "d2.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    d=new D3;
    d->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    D2 d;
    d.setModal(true);
    d.exec();
}
