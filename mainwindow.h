#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"d3.h"
#include"d4.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    D3 *d;
    D4 *m;
};

#endif // MAINWINDOW_H
