#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "figure.h"
#include <cmath>

class Tetrahedron : public Figure
{
public:
    Tetrahedron(Figure* parent = nullptr);

    QVector<Polygon> GetPolygons() override;
    void SetEdge(double _edge);

private:
    void CalculatePoints() override;

    double edge = 10;
};

#endif // TETRAHEDRON_H
