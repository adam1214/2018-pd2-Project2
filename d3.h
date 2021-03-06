#ifndef D3_H
#define D3_H

#include <QMainWindow>
#include <QDialog>
//#include <Qtcore>
#include <QtGui>
#include <delegate.h>
#include<QTableWidgetItem>

namespace Ui {
class D3;
}

class D3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit D3(QWidget *parent = 0);
    ~D3();

private slots:
    void on_pushButton_clicked(); //check

    void on_pushButton_2_clicked(); //show solution

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::D3 *ui;
    QStandardItemModel *model;
    Delegate *mydelegate;

};

#endif // D3_H
