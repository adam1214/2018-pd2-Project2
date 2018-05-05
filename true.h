#ifndef TRUE_H
#define TRUE_H

#include <QDialog>

namespace Ui {
class True;
}

class True : public QDialog
{
    Q_OBJECT

public:
    explicit True(QWidget *parent = 0);
    ~True();

private:
    Ui::True *ui;
};

#endif // TRUE_H
