#ifndef D4_H
#define D4_H

#include <QMainWindow>
#include <QDialog>
//#include <Qtcore>
#include <QtGui>
#include <delegate.h>
#include<QTableWidgetItem>

namespace Ui {
class D4;
}

class D4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit D4(QWidget *parent = 0);
    ~D4();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_3_clicked();

private:
    Ui::D4 *ui;
    QStandardItemModel *model;
    Delegate *mydelegate;
};

#endif // D4_H
