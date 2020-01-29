#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "filling.h"
#include "battletable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_released();

    void on_buttleTableBtn_released();

private:
    Ui::MainWindow *ui;
    Filling *filling;
    BattleTable *battleTable;
};
#endif // MAINWINDOW_H
