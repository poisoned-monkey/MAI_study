#ifndef PYRAMID_H
#define PYRAMID_H

#include "figure.h"
#include <QtMath>

class Pyramid : public Figure
{
public:
    Pyramid(Figure* parent = nullptr);
    virtual QVector<Polygon> GetPolygons() override;

    void SetHeight(double _height);
    void SetLowerRadius(double _lower);
    void SetUpperRadius(double _upper);
    void SetEdgeCount(int _count);

    QVector4D GetInnerPoint();

private:
    virtual void CalculatePoints() override;
    double height = 2;
    double lower_radius = 1;
    double upper_radius = 0.5;
    int edge_count = 8;
};

#endif // PYRAMID_H
