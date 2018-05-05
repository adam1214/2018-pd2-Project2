#ifndef D3_H
#define D3_H

#include <QMainWindow>
#include <QDialog>
#include <Qtcore>
#include <QtGui>
#include <delegate.h>

namespace Ui {
class D3;
}

class D3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit D3(QWidget *parent = 0);
    ~D3();
    int a[9][9];

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellDoubleClicked();

private:
    Ui::D3 *ui;
    QStandardItemModel *model;
    Delegate *mydelegate;

};

#endif // D3_H
