#ifndef FILLING_H
#define FILLING_H

#include <QDialog>

namespace Ui {
class Filling;
}

class Filling : public QDialog
{
    Q_OBJECT

public:
    explicit Filling(QWidget *parent = nullptr);
    ~Filling();

private:
    Ui::Filling *ui;
};

#endif // FILLING_H
