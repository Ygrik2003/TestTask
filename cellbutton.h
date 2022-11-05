#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QWidget>

enum Color
{
    Red,
    Green,
    Blue,
    None
};

enum Type
{
    Colored,
    Blocked,
    Passed
};

class CellButton : public QPushButton
{
    Q_OBJECT
public:
    CellButton() {}
    CellButton(Type type, QPoint position, Color color = Color::None, QWidget *parent = nullptr);

    void setCellParams(Type type, QPoint position, Color color = Color::None);

    Color color;
    QPoint position;
    Type type;

signals:
    void selectedSignal(QPoint);
    void unselectedSignal(QPoint);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    //QGraphicsDropShadowEffect shadow;
};

#endif // CELLBUTTON_H
