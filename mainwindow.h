#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cellbutton.h"

#include <QMainWindow>
#include <QVector>
#include <methods.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const int COUNT_ROWS = 5;
const int COUNT_BLOCKED = 6;
const int COUNT_TYPES = sizeof(Type);
const int COUNT_COLORS = sizeof(Color);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handlerSelectedSlot(QPoint);
    void handlerUnselectedSlot(QPoint);


private:
    Ui::MainWindow *ui;

    QVector<QVector<CellButton *>> cells;

    void fillCells();
    void swapCells(QPoint, QPoint);
    bool checkWin();
    void winMessageBox();

    QPoint selectedCell = QPoint(-1, -1);
};
#endif // MAINWINDOW_H
