#ifndef PYRAMID_H
#define PYRAMID_H

#include <QObject>
#include <QWidget>
#include <QtMath>
#include <algorithm>
#include "figure.h"

class Pyramid : public Figure
{
    Q_OBJECT
public:
    Pyramid(Figure* parent = nullptr);
    Pyramid(double _height, double _lower_radius, double _upper_radius);

    void changeParameters(double _height, double _lower_radius, double _upper_radius);


private:

    static constexpr int POINT_COUNT = 8;
    void calculatePoints();
    void producePolygons() override;
    double height = 2, lower_radius = 1, upper_radius = 0.5;

};

#endif // PYRAMID_H
