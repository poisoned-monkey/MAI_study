#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include <QObject>
#include <QPainter>
#include <QWidget>

class Square : public Figure
{
    Q_OBJECT
public:
    Square(double _size);
    Square(Figure* parent = nullptr);

private:

    static constexpr int POINT_COUNT = 4;
    void calculatePoints();

    void producePolygons() override;

    double size;

};

#endif // SQUARE_H
