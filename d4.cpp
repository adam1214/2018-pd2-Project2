#include "d4.h"
#include "ui_d4.h"
#include <cstdlib>
#include <cstdio>
#include "true.h"
#include "false.h"
#include "delegate.h"
#include <QString>
#include <iostream>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QDebug>
#include "mainwindow.h"
#include <QFile>

int sudoku4[81];
int tempNum4[81];
int tempSp4=0;
int startH4[81];
int startV4[81];
int startB4[81];
int addH4[9];
int addV4[9];
int addB4[9];
int a4[9][9]={0};

int init4()
{
    int i;
    for(i=0;i<81;i++)
    {
        startH4[i]=i/9*9;
        startV4[i]=i%9;
        startB4[i]=((i/9)/3)*27+((i%9)/3)*3;
    }
    for (i = 0; i<9; i++)
    {
            addH4[i] = i;                              // 列位置的加值
            addV4[i] = i * 9;                            // 行位置的加值
            addB4[i] = (i / 3) * 9 + (i % 3);                 // 九宮格位置的加值
    }
}
int getNextBlank4(int sp)
{
    // 取得下一個空白的位置
    do {
        sp++;
    } while (sp<81 && sudoku4[sp]>0);
    return(sp);
}
int push4(int sp) {
    // 將指定的位置放入堆疊中
    tempNum4[tempSp4++] = sp;
}

int pop4() {
    // 取出堆疊中的上一個位置
    if (tempSp4 <= 0) return(-1);
    else return(tempNum4[--tempSp4]);
}
int check14(int sp, int start, int *addnum) {
    // 檢查指定的行、列、九宮格有沒有相同的數字，若有傳回 1
    int fg = 0, i, sp1;
    for (i = 0; i<9; i++) {
        sp1 = start + addnum[i];
        if (sp != sp1 && sudoku4[sp] == sudoku4[sp1]) fg++;
    }
    return(fg);
}
int check4(int sp) {
    // 檢查同行、列、九宮格有沒有相同的數字，若有傳回 1
    int fg = 0;
    if (!fg) fg = check14(sp, startH4[sp], addH4);   // 檢查同列有沒有相同的數字
    if (!fg) fg = check14(sp, startV4[sp], addV4);   // 檢查同行有沒有相同的數字
    if (!fg) fg = check14(sp, startB4[sp], addB4);   // 檢查同九宮格有沒有相同的數字
    return(fg);
}


int tryAns4() {
    // 測試求解
    int sp = getNextBlank4(-1);                    // 取得第一個空白的位置開始填入數字
    do {
        sudoku4[sp]++;                            // 將本位置數字加 1
        if (sudoku4[sp]>9) {                        // 如果本位置的數字已大於 9 時則回到上一個位置繼續測試
            sudoku4[sp] = 0;
            sp = pop4();
        }
        else {
            if (check4(sp) == 0) {                     // 如果同行、列、九宮格都沒有相同的數字，則到下一個空白處繼續
                push4(sp);                          // 當然，如果發現有相同的數字時，就需把原位置的數字加 1(所以本處什麼都不做)
                sp = getNextBlank4(sp);
            }
        }
    } while (sp >= 0 && sp<81);
}

D4::D4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::D4)
{
    int i,j;

    ui->setupUi(this);
    mydelegate=new Delegate(this);
    model=new QStandardItemModel(9,9,this);

    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(a4[row][col]));
            ui->tableWidget->setItem(row,col,item);
            //item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            item->setTextAlignment((Qt::AlignCenter));
        }
    }
}

D4::~D4()
{
    delete ui;
}

void D4::on_pushButton_clicked()
{
    int location,i,j,check_row=1,check_col=1,check_cell=1;
    int arr_untiy[9]={0};
    for(i=0;i<9;i++) //check rows
    {
        for(j=0;j<9;j++)
        {
            arr_untiy[j]=0;
        }
        for(j=0;j<9;j++)
        {
             arr_untiy[a4[i][j]-1]= arr_untiy[a4[i][j]-1]+1;
        }
        for(j=0;j<9;j++)
        {
            if(arr_untiy[j]!=1)
            {
               check_row=0;
            }
            if(check_row==0)
            {
                break;
            }
        }
        if(check_row==0)
        {
            break;
        }
    }
    for(j=0;j<9;j++) //check cols
    {
        for(i=0;i<9;i++)
        {
            arr_untiy[i]=0;
        }
        for(i=0;i<9;i++)
        {
             arr_untiy[a4[i][j]-1]= arr_untiy[a4[i][j]-1]+1;
        }
        for(i=0;i<9;i++)
        {
            if(arr_untiy[i]!=1)
            {
               check_col=0;
            }
            if(check_col==0)
            {
                break;
            }
        }
        if(check_col==0)
        {
            break;
        }
    }
    int cell_0[9]={0},cell_1[9]={0},cell_2[9]={0},cell_3[9]={0},cell_4[9]={0},cell_5[9]={0},cell_6[9]={0},cell_7[9]={0},cell_8[9]={0};

    for(i=0;i<9;i++) //check cells
    {
        for(j=0;j<9;j++)
        {
            location = 27*(i/3) + 3*(i%3) + 9*(j/3) + (j%3);
            if(location>=0&&location<=8)
            {
                cell_0[a4[i][j]-1]++;
            }
            else if(location>=9&&location<=17)
            {
                cell_1[a4[i][j]-1]++;
            }
            else if(location>=18&&location<=26)
            {
                cell_2[a4[i][j]-1]++;
            }
            else if(location>=27&&location<=35)
            {
                cell_3[a4[i][j]-1]++;
            }
            else if(location>=36&&location<=44)
            {
                cell_4[a4[i][j]-1]++;
            }
            else if(location>=45&&location<=53)
            {
                cell_5[a4[i][j]-1]++;
            }
            else if(location>=54&&location<=62)
            {
                cell_6[a4[i][j]-1]++;
            }
            else if(location>=63&&location<=71)
            {
                cell_7[a4[i][j]-1]++;
            }
            else if(location>=72&&location<=80)
            {
                cell_8[a4[i][j]-1]++;
            }
        }

    }

    for(i=0;i<9;i++)
    {
        if(cell_0[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_1[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_2[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_3[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_4[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_5[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_6[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_7[i]!=1)
        {
            check_cell=0;
        }
    }
    for(i=0;i<9;i++)
    {
        if(cell_8[i]!=1)
        {
            check_cell=0;
        }
    }
    if(check_row==1&&check_col==1&&check_cell==1)
    {
        True t;
        t.setModal(true);
        t.exec();
    }
    else
    {
        False f;
        f.setModal(true);
        f.exec();
        qDebug() << "check_row = "<<check_row;
        qDebug() << "check_col = "<<check_col;
        qDebug() << "check_cell = "<<check_cell;
    }
}

void D4::on_pushButton_2_clicked()
{
    init4();
    tryAns4();
    int b[9][9]={0};
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            b[i][j]=sudoku4[i*9+j];
        }
    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
          QTableWidgetItem* item = new QTableWidgetItem(QString::number(b[row][col]));
          ui->tableWidget->setItem(row,col,item);
          item->setTextAlignment((Qt::AlignCenter));
          if(sudoku4[row*9+col]!=0)
          {
               item->setBackgroundColor(QColor(200,111,100));
          }
        }
    }
}

void D4::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    int current_row=ui->tableWidget->currentRow();
    int current_col=ui->tableWidget->currentColumn();
    //QTableWidgetItem* item = ui->tableWidget->item(row,column);
    a4[current_row][current_col]=item->text().toInt();
    QString str;
    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
        {
            str.append(QString::number(a4[i][j]));
            str.append(' ');
            if(j==8)
            {
                str.append('\n');
            }
        }
    }
    //ui->textEdit->setPlainText(str);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            sudoku4[i*9+j]=a4[i][j];
        }
}

void D4::on_pushButton_3_clicked()
{
    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(a4[row][col]==0)
            {
                QTableWidgetItem* item = new QTableWidgetItem();
                ui->tableWidget->setItem(row,col,item);
                item->setTextAlignment((Qt::AlignCenter));
            }
            if(a4[row][col]!=0)
            {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(a4[row][col]));
                ui->tableWidget->setItem(row,col,item);
                item->setBackgroundColor(QColor(200,111,100));
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setTextAlignment((Qt::AlignCenter));
            }
        }
    }
}
