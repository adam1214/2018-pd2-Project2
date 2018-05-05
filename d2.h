#ifndef D2_H
#define D2_H

#include <QDialog>

namespace Ui {
class D2;
}

class D2 : public QDialog
{
    Q_OBJECT

public:
    explicit D2(QWidget *parent = 0);
    ~D2();

private:
    Ui::D2 *ui;
};

#endif // D2_H
