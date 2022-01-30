#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "figure.h"
#include <QObject>
#include <QtMath>
#include <cmath>
#include <QWidget>

class Ellipsoid : public Figure
{
    Q_OBJECT
public:
    Ellipsoid(Figure* parent = nullptr);


    QVector4D GetInnerPoint();
    void SetLayersCount(int _count);
    void SetPointsCount(int _count);
    void SetEllipsoidCoefs(double _a, double _b, double _c);
    void SetTruncCoefs(double _upper, double _lower);

    QVector<Polygon> GetPolygons() override;

private:
    void CalculatePoints() override;

    int layers_count = 100, layer_points_count = 100;
    double a = 1, b = 1, c = 1; // ellipsoid parameters
    double upper_trunc = 1, lower_trunc = -1; // number between -1 and 1

};

#endif // ELLIPSOID_H
