#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <qlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand( time(0) );

    cells.resize(COUNT_ROWS);
    for (int i = 0; i < COUNT_ROWS; i++)
    {
        cells[i].resize(COUNT_ROWS);
        for (int j = 0; j < COUNT_ROWS; j++)
            cells[i][j] = new CellButton();
    }
    fillCells();

    QLabel *lblColor;


    lblColor = new QLabel(this);
    lblColor->setStyleSheet("background-color: red");
    lblColor->setGeometry(
                QRect(
                    QPoint(ui->cells->x() + 2 * ui->gridLayout->horizontalSpacing(), ui->cells->y() - 50),
                    QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, 40)
                    )
                );

    lblColor = new QLabel(this);
    lblColor->setStyleSheet("background-color: green");
    lblColor->setGeometry(
                QRect(
                    QPoint(ui->cells->x() + ui->gridLayout->horizontalSpacing()  + 2 * ui->cells->width() / COUNT_ROWS, ui->cells->y() - 50),
                    QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, 40)
                    )
                );

    lblColor = new QLabel(this);
    lblColor->setStyleSheet("background-color: blue");
    lblColor->setGeometry(
                QRect(
                    QPoint(ui->cells->x() + 4 * ui->cells->width() / COUNT_ROWS, ui->cells->y() - 50),
                    QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, 40)
                    )
                );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlerSelectedSlot(QPoint cell)
{
    if (selectedCell == QPoint(-1, -1))
    {
        selectedCell = cell;
        return ;
    }

    QPoint distance = selectedCell - cell;

    if (selectedCell != QPoint(-1, -1) && (abs(distance.x() + distance.y()) == 1) && cells[cell.x()][cell.y()]->type != Type::Colored)
    {
        swapCells(selectedCell, cell);
        if (checkWin())
            winMessageBox();
    }
    else
    {
        cells[selectedCell.x()][selectedCell.y()]->setChecked(false);
        selectedCell = cell;
    }
}

void MainWindow::handlerUnselectedSlot(QPoint cell)
{
    if (selectedCell == cell)
        selectedCell = QPoint(-1, -1);
}

void MainWindow::fillCells()
{
    QPoint point;
    QVector<QPoint> history;




    for (int i = 0; i < COUNT_BLOCKED; i++)
    {
            point = QPoint(rand() % COUNT_ROWS, (2 * i + 1) % (COUNT_ROWS - 1));
            while (methods::searchElement(history, point))
                point = QPoint(rand() % COUNT_ROWS, (2 * i + 1) % (COUNT_ROWS - 1));

            cells[point.x()][point.y()]->setCellParams(Type::Blocked, point);
            cells[point.x()][point.y()]->setFixedSize(QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, (ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS));
            ui->gridLayout->addWidget(cells[point.x()][point.y()], point.x(), point.y());

            connect(cells[point.x()][point.y()], &CellButton::selectedSignal, this, &MainWindow::handlerSelectedSlot);
            connect(cells[point.x()][point.y()], &CellButton::unselectedSignal, this, &MainWindow::handlerSelectedSlot);

            history.push_back(point);
        }

    for (int color = 0; color != Color::None; color++)
    {
        for (int i = 0; i < 5; i++)
        {
            point = QPoint(rand() % COUNT_ROWS, rand() % COUNT_ROWS);
            while (methods::searchElement(history, point))
                point = QPoint(rand() % COUNT_ROWS, rand() % COUNT_ROWS);

            cells[point.x()][point.y()]->setCellParams(Type::Colored, point, (Color)color);
            cells[point.x()][point.y()]->setFixedSize(QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, (ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS));
            ui->gridLayout->addWidget(cells[point.x()][point.y()], point.x(), point.y());

            connect(cells[point.x()][point.y()], &CellButton::selectedSignal, this, &MainWindow::handlerSelectedSlot);
            connect(cells[point.x()][point.y()], &CellButton::unselectedSignal, this, &MainWindow::handlerSelectedSlot);

            history.push_back(point);
        }
    }

    for (int i = 0; i < COUNT_ROWS; i++)
    {
        for (int j = 0; j < COUNT_ROWS; j++)
        {
            point = QPoint(i, j);
            if (methods::searchElement(history, point))
                continue;

            cells[point.x()][point.y()]->setCellParams(Type::Passed, point);
            cells[point.x()][point.y()]->setFixedSize(QSize((ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS, (ui->cells->width() - 4 * ui->gridLayout->horizontalSpacing()) / COUNT_ROWS));
            ui->gridLayout->addWidget(cells[point.x()][point.y()], point.x(), point.y());

            connect(cells[point.x()][point.y()], &CellButton::selectedSignal, this, &MainWindow::handlerSelectedSlot);
            connect(cells[point.x()][point.y()], &CellButton::unselectedSignal, this, &MainWindow::handlerSelectedSlot);

            history.push_back(point);
        }
    }
}

void MainWindow::swapCells(QPoint firstCell, QPoint secondCell)
{
    std::swap(cells[firstCell.x()][firstCell.y()], cells[secondCell.x()][secondCell.y()]);
    std::swap(cells[firstCell.x()][firstCell.y()]->position, cells[secondCell.x()][secondCell.y()]->position);

    ui->gridLayout->addWidget(cells[firstCell.x()][firstCell.y()], firstCell.x(), firstCell.y());
    ui->gridLayout->addWidget(cells[secondCell.x()][secondCell.y()], secondCell.x(), secondCell.y());

    cells[firstCell.x()][firstCell.y()]->setChecked(false);
    cells[secondCell.x()][secondCell.y()]->setChecked(false);
    selectedCell = QPoint(-1, -1);
}

bool MainWindow::checkWin()
{
    for (int i = 0; i < COUNT_ROWS; i++)
    {
        for (int j = 0; j < COUNT_ROWS; j += 2)
        {
            if (cells[i][j]->color != (Color)(j / 2))
                return false;
        }
    }
    return true;
}

void MainWindow::winMessageBox()
{
    QMessageBox winMsgBox;
    winMsgBox.setText("Win");
    winMsgBox.exec();
    fillCells();
}
