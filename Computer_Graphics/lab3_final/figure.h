#ifndef FIGURE_H
#define FIGURE_H

#include <QVector>
#include <QVector4D>
#include <QVector3D>
#include <QColor>
#include <QObject>

class Polygon : public QVector<QVector4D> {
public:
    Polygon() = default;
    Polygon(std::initializer_list<QVector4D> list);
    Polygon(Polygon&& other);
    Polygon(const Polygon& other);
    Polygon& operator = (Polygon&& other);
    Polygon& operator = (const Polygon& other);
    QVector4D Center() const;


    QVector4D GetNormal(QVector4D check_point) const;
    QVector3D GetReflection(QVector4D view_point, QVector4D check_point) const;

    QColor color = Qt::transparent;
};

double GetSum(QVector4D v);
QVector4D GetPlaneEquation(const Polygon& p);

class Figure : public QObject
{
    Q_OBJECT
public:
    Figure() = default;
    Figure(QObject* parent = nullptr);
    virtual ~Figure() = default;
    virtual QVector<Polygon> GetPolygons() = 0;

protected:
    virtual void CalculatePoints() = 0;
    QVector<QVector4D> points;

    mutable QVector<Polygon> polygon_cache;
    mutable bool changed = true;
};

#endif // FIGURE_H
