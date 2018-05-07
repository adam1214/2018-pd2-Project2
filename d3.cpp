#include "d3.h"
#include "ui_d3.h"
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

int sudoku[81];
int tempNum[81];
int tempSp=0;
int startH[81];
int startV[81];
int startB[81];
int addH[9];
int addV[9];
int addB[9];
static int a[9][9]={
                    1,4,5,3,2,7,6,9,8,
                    8,3,9,6,5,4,1,2,7,
                    6,7,2,9,1,8,5,4,3,
                    4,9,6,1,8,5,3,7,2,
                    2,1,8,4,7,3,9,5,6,
                    7,5,3,2,9,6,4,8,1,
                    3,6,7,5,4,2,8,1,9,
                    9,8,4,7,6,1,2,3,5,
                    5,2,1,8,3,9,7,6,4
                };

int init()
{
    int i;
    for(i=0;i<81;i++)
    {
        startH[i]=i/9*9;
        startV[i]=i%9;
        startB[i]=((i/9)/3)*27+((i%9)/3)*3;
    }
    for (i = 0; i<9; i++)
    {
            addH[i] = i;                              // 列位置的加值
            addV[i] = i * 9;                            // 行位置的加值
            addB[i] = (i / 3) * 9 + (i % 3);                 // 九宮格位置的加值
    }
}
int getNextBlank(int sp)
{
    // 取得下一個空白的位置
    do {
        sp++;
    } while (sp<81 && sudoku[sp]>0);
    return(sp);
}
int push(int sp) {
    // 將指定的位置放入堆疊中
    tempNum[tempSp++] = sp;
}

int pop() {
    // 取出堆疊中的上一個位置
    if (tempSp <= 0) return(-1);
    else return(tempNum[--tempSp]);
}
int check1(int sp, int start, int *addnum) {
    // 檢查指定的行、列、九宮格有沒有相同的數字，若有傳回 1
    int fg = 0, i, sp1;
    for (i = 0; i<9; i++) {
        sp1 = start + addnum[i];
        if (sp != sp1 && sudoku[sp] == sudoku[sp1]) fg++;
    }
    return(fg);
}
int check(int sp) {
    // 檢查同行、列、九宮格有沒有相同的數字，若有傳回 1
    int fg = 0;
    if (!fg) fg = check1(sp, startH[sp], addH);   // 檢查同列有沒有相同的數字
    if (!fg) fg = check1(sp, startV[sp], addV);   // 檢查同行有沒有相同的數字
    if (!fg) fg = check1(sp, startB[sp], addB);   // 檢查同九宮格有沒有相同的數字
    return(fg);
}


int tryAns() {
    // 測試求解
    int sp = getNextBlank(-1);                    // 取得第一個空白的位置開始填入數字
    do {
        sudoku[sp]++;                            // 將本位置數字加 1
        if (sudoku[sp]>9) {                        // 如果本位置的數字已大於 9 時則回到上一個位置繼續測試
            sudoku[sp] = 0;
            sp = pop();
        }
        else {
            if (check(sp) == 0) {                     // 如果同行、列、九宮格都沒有相同的數字，則到下一個空白處繼續
                push(sp);                          // 當然，如果發現有相同的數字時，就需把原位置的數字加 1(所以本處什麼都不做)
                sp = getNextBlank(sp);
            }
        }
    } while (sp >= 0 && sp<81);
}

D3::D3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::D3)
{
    /*QFile file("sample");
    file.open(QIODevice::ReadOnly);
    int s=-1;
    while(!file.atEnd())
    {
        QString str=file.readLine();

        s=s+1;
        for(int j=0;j<=9;j++)
        {
            a[s][j]=str[j].unicode()-'1'+1;
        }
    }*/
    /*a[9][9]={
                    1,4,5,3,2,7,6,9,8,
                    8,3,9,6,5,4,1,2,7,
                    6,7,2,9,1,8,5,4,3,
                    4,9,6,1,8,5,3,7,2,
                    2,1,8,4,7,3,9,5,6,
                    7,5,3,2,9,6,4,8,1,
                    3,6,7,5,4,2,8,1,9,
                    9,8,4,7,6,1,2,3,5,
                    5,2,1,8,3,9,7,6,4
                };*/
    a[0][0]=1;
    a[0][1]=4;
    a[0][2]=5;
    a[0][3]=3;
    a[0][4]=2;
    a[0][5]=7;
    a[0][6]=6;
    a[0][7]=9;
    a[0][8]=8;

    a[1][0]=8;
    a[1][1]=3;
    a[1][2]=9;
    a[1][3]=6;
    a[1][4]=5;
    a[1][5]=4;
    a[1][6]=1;
    a[1][7]=2;
    a[1][8]=7;

    a[2][0]=6;
    a[2][1]=7;
    a[2][2]=2;
    a[2][3]=9;
    a[2][4]=1;
    a[2][5]=8;
    a[2][6]=5;
    a[2][7]=4;
    a[2][8]=3;

    a[3][0]=4;
    a[3][1]=9;
    a[3][2]=6;
    a[3][3]=1;
    a[3][4]=8;
    a[3][5]=5;
    a[3][6]=3;
    a[3][7]=7;
    a[3][8]=2;

    a[4][0]=2;
    a[4][1]=1;
    a[4][2]=8;
    a[4][3]=4;
    a[4][4]=7;
    a[4][5]=3;
    a[4][6]=9;
    a[4][7]=5;
    a[4][8]=6;

    a[5][0]=7;
    a[5][1]=5;
    a[5][2]=3;
    a[5][3]=2;
    a[5][4]=9;
    a[5][5]=6;
    a[5][6]=4;
    a[5][7]=8;
    a[5][8]=1;

    a[6][0]=3;
    a[6][1]=6;
    a[6][2]=7;
    a[6][3]=5;
    a[6][4]=4;
    a[6][5]=2;
    a[6][6]=8;
    a[6][7]=1;
    a[6][8]=9;

    a[7][0]=9;
    a[7][1]=8;
    a[7][2]=4;
    a[7][3]=7;
    a[7][4]=6;
    a[7][5]=1;
    a[7][6]=2;
    a[7][7]=3;
    a[7][8]=5;

    a[8][0]=5;
    a[8][1]=2;
    a[8][2]=1;
    a[8][3]=8;
    a[8][4]=3;
    a[8][5]=9;
    a[8][6]=7;
    a[8][7]=6;
    a[8][8]=4;

    //先做旋轉
    int a1[9][9];
    int r1=rand()%4,k,i,j,con,temp;
    for(k=r1;k>=0;k--)
    {
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                a1[i][j]=a[j][i];
            }
        }
        con=8;
        for(j=0;j<4;j++)
        {
            for(i=0;i<9;i++)
            {
                temp=a1[i][j];
                a1[i][j]=a1[i][j+con];
                a1[i][j+con]=temp;
            }
            con=con-2;
        }
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                a[i][j]=a1[i][j];
            }
        }
    }
    //做行行列列對調
    int r2=rand()%18;
    if(r2==17)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][0];
            a[i][0]=a[i][1];
            a[i][1]=temp;
        }
        r2--;
    }
    if(r2==16)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][1];
            a[i][1]=a[i][2];
            a[i][2]=temp;
        }
        r2--;
    }
    if(r2==15)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][0];
            a[i][0]=a[i][2];
            a[i][2]=temp;
        }
        r2--;
    }
    if(r2==14)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][3];
            a[i][3]=a[i][4];
            a[i][4]=temp;
        }
        r2--;
    }
    if(r2==13)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][4];
            a[i][4]=a[i][5];
            a[i][5]=temp;
        }
        r2--;
    }
    if(r2==12)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][3];
            a[i][3]=a[i][5];
            a[i][5]=temp;
        }
        r2--;
    }
    if(r2==11)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][6];
            a[i][6]=a[i][7];
            a[i][7]=temp;
        }
        r2--;
    }
    if(r2==10)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][7];
            a[i][7]=a[i][8];
            a[i][8]=temp;
        }
        r2--;
    }
    if(r2==9)
    {
        for(i=0;i<9;i++)
        {
            temp=a[i][6];
            a[i][6]=a[i][8];
            a[i][8]=temp;
        }
        r2--;
    }
    if(r2==8)
    {
        for(j=0;j<9;j++)
        {
            temp=a[0][j];
            a[0][j]=a[1][j];
            a[1][j]=temp;
        }
        r2--;
    }
    if(r2==7)
    {
        for(j=0;j<9;j++)
        {
            temp=a[1][j];
            a[1][j]=a[2][j];
            a[2][j]=temp;
        }
        r2--;
    }
    if(r2==6)
    {
        for(j=0;j<9;j++)
        {
            temp=a[0][j];
            a[0][j]=a[2][j];
            a[2][j]=temp;
        }
        r2--;
    }
    if(r2==5)
    {
        for(j=0;j<9;j++)
        {
            temp=a[3][j];
            a[3][j]=a[4][j];
            a[4][j]=temp;
        }
        r2--;
    }
    if(r2==4)
    {
        for(j=0;j<9;j++)
        {
            temp=a[4][j];
            a[4][j]=a[5][j];
            a[5][j]=temp;
        }
        r2--;
    }
    if(r2==3)
    {
        for(j=0;j<9;j++)
        {
            temp=a[3][j];
            a[3][j]=a[5][j];
            a[5][j]=temp;
        }
        r2--;
    }
    if(r2==2)
    {
        for(j=0;j<9;j++)
        {
            temp=a[6][j];
            a[6][j]=a[7][j];
            a[7][j]=temp;
        }
        r2--;
    }
    if(r2==1)
    {
        for(j=0;j<9;j++)
        {
            temp=a[7][j];
            a[7][j]=a[8][j];
            a[8][j]=temp;
        }
        r2--;
    }
    if(r2==0)
    {
        for(j=0;j<9;j++)
        {
            temp=a[6][j];
            a[6][j]=a[8][j];
            a[8][j]=temp;
        }
        r2--;
    }
    //挖空格填零
    int r3=(rand()%10)+30;
    for(k=0;k<r3;k++)
    {
        i=rand()%10;
        j=rand()%10;
        while(a[i][j]==0)
        {
            i=rand()%10;
            j=rand()%10;
        }
        a[i][j]=0;
    }
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            sudoku[i*9+j]=a[i][j];
        }
    ui->setupUi(this);

    mydelegate=new Delegate(this);
    model=new QStandardItemModel(9,9,this);

    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(a[row][col]==0)
            {
                QTableWidgetItem* item = new QTableWidgetItem();
                ui->tableWidget->setItem(row,col,item);
                item->setTextAlignment((Qt::AlignCenter));

            }
            if(a[row][col]!=0)
            {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(a[row][col]));
                ui->tableWidget->setItem(row,col,item);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setBackgroundColor(QColor(200,111,100));
                item->setTextAlignment((Qt::AlignCenter));
            }
        }
    }


}
D3::~D3()
{
    delete ui;
}
void D3::on_pushButton_clicked()
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
             arr_untiy[a[i][j]-1]= arr_untiy[a[i][j]-1]+1;
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
             arr_untiy[a[i][j]-1]= arr_untiy[a[i][j]-1]+1;
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
                cell_0[a[i][j]-1]++;
            }
            else if(location>=9&&location<=17)
            {
                cell_1[a[i][j]-1]++;
            }
            else if(location>=18&&location<=26)
            {
                cell_2[a[i][j]-1]++;
            }
            else if(location>=27&&location<=35)
            {
                cell_3[a[i][j]-1]++;
            }
            else if(location>=36&&location<=44)
            {
                cell_4[a[i][j]-1]++;
            }
            else if(location>=45&&location<=53)
            {
                cell_5[a[i][j]-1]++;
            }
            else if(location>=54&&location<=62)
            {
                cell_6[a[i][j]-1]++;
            }
            else if(location>=63&&location<=71)
            {
                cell_7[a[i][j]-1]++;
            }
            else if(location>=72&&location<=80)
            {
                cell_8[a[i][j]-1]++;
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
void D3::on_pushButton_2_clicked()
{
    int sudoku2[81];
    for(int i=0;i<81;i++)
    {
        sudoku2[i]=sudoku[i];
    }
    init();
    tryAns();
    int b[9][9]={0};
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            b[i][j]=sudoku[i*9+j];
        }


    for(int row=0;row<9;row++)
    {
        for(int col=0;col<9;col++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(b[row][col]));
            ui->tableWidget->setItem(row,col,item);
            item->setTextAlignment((Qt::AlignCenter));
            if(sudoku2[row*9+col]!=0)
            {
                 item->setBackgroundColor(QColor(200,111,100));
            }
        }
    }
    /*QString str;
    int cnt=0;
    for(int i=0;i<81;++i)
    {
        str.append(QString::number(sudoku2[i]));
        str.append(' ');
        cnt++;
        if(cnt==9)
        {
            cnt=0;
            str.append('\n');
        }
    }*/
    //ui->textEdit->setPlainText(str);
}
/*void D3::on_tableWidget_cellDoubleClicked(int row, int column)
{
    //int current_row=ui->tableWidget->currentRow();
    //int current_col=ui->tableWidget->currentColumn();
    QTableWidgetItem* item = ui->tableWidget->item(row,column);
    a[row][column]=item->text().toInt();
    QString str;
    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
        {
            str.append(QString::number(a[i][j]));
            str.append(' ');
            if(j==8)
            {
                str.append('\n');
            }
        }
    }
    ui->textEdit->setPlainText(str);
}*/

void D3::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    int current_row=ui->tableWidget->currentRow();
    int current_col=ui->tableWidget->currentColumn();
    //QTableWidgetItem* item = ui->tableWidget->item(row,column);
    a[current_row][current_col]=item->text().toInt();
    /*QString str;
    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
        {
            str.append(QString::number(a[i][j]));
            str.append(' ');
            if(j==8)
            {
                str.append('\n');
            }
        }
    }
    ui->textEdit->setPlainText(str);*/
}
