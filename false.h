#ifndef FALSE_H
#define FALSE_H

#include <QDialog>

namespace Ui {
class False;
}

class False : public QDialog
{
    Q_OBJECT

public:
    explicit False(QWidget *parent = 0);
    ~False();

private:
    Ui::False *ui;
};

#endif // FALSE_H
