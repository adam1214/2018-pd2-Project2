#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "d3.h"
#include "d4.h"
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
    m=new D4;
    m->show();
}
