#include "cellbutton.h"
#include <QDebug>

CellButton::CellButton(Type type, QPoint position, Color color, QWidget *parent) : QPushButton(parent)
{
    setCellParams(type, position, color)
}

void CellButton::setCellParams(Type type, QPoint position, Color color)
{
    this->setCheckable(true);
    this->position = position;
    this->type = type;
    this->color = color;
    switch (type)
    {
    case Colored:
        switch (color)
        {
        case Red:
            this->setStyleSheet("background-color: red");
            break;
        case Green:
            this->setStyleSheet("background-color: green");
            break;
        case Blue:
            this->setStyleSheet("background-color: blue;");
            break;
        case None:
            this->setStyleSheet("background-color: black");
            break;
        }

        break;
    case Passed:
        this->setStyleSheet("background-color: rgba(0,0,0,0)");
        break;
    case Type::Blocked:
        this->setStyleSheet("background-color: black");

        this->setDisabled(true);
        break;
    }
}


void CellButton::mousePressEvent(QMouseEvent *)
{
    if (type != Type::Passed)
    {
        if (this->isChecked())
        {
            emit selectedSignal(this->position);
            this->setChecked(false);
        }
        else
        {
            emit unselectedSignal(this->position);
            this->setChecked(true);
        }
    }
    else
    {
        emit selectedSignal(this->position);
    }
}
