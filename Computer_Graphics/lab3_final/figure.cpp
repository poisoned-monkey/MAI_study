#include "figure.h"

Figure::Figure(QObject* parent)
    : QObject(parent) {}



Polygon::Polygon(std::initializer_list<QVector4D> list)
    : QVector<QVector4D>(list){}


QVector4D Polygon::Center() const {
    QVector4D result;
    for (QVector4D v : *this) {
        result += v;
    }
    result /= size();
    return result;
}

Polygon::Polygon(Polygon&& other)
    : QVector<QVector4D>(static_cast<QVector<QVector4D>&&>(other)), color(std::move(other.color)) {}

Polygon::Polygon(const Polygon& other)
    : QVector<QVector4D>(static_cast<const QVector<QVector4D>&>(other)), color(other.color) {}

Polygon& Polygon::operator = (Polygon&& other) {
    QVector<QVector4D>::operator =(static_cast<QVector<QVector4D>&&> (other));
    color = std::move(other.color);
    return *this;
}
Polygon& Polygon::operator = (const Polygon& other) {
    QVector<QVector4D>::operator =(static_cast<const QVector<QVector4D>&> (other));
    color = other.color;
    return *this;
}

QVector4D Polygon::GetNormal(QVector4D check_point) const {
    QVector4D equation = GetPlaneEquation(*this);
    QVector4D check = check_point * equation;
    double sum = check.x() + check.y() + check.z() + check.w();
    if (sum > 0) {
        equation *= -1;
    }
    equation.setW(1);
    return equation;
}

double GetSum(QVector4D v) {
    return v.x() + v.y() + v.z() + v.w();
}

QVector3D Polygon::GetReflection(QVector4D view_point, QVector4D check_point) const {
    QVector3D n = GetNormal(check_point).toVector3D();
    QVector3D l = view_point.toVector3DAffine() - Center().toVector3DAffine();
    n.normalize();
    l.normalize();
    QVector4D eq_second = {n.z() * l.y() - n.y() * l.z(),
                           n.x() * l.z() - n.z() * l.x(),
                           n.y() * l.x() - n.x() * l.y(),
                           n.x() * l.x() + n.y() * l.y() + n.z() * l.z()};
    QVector3D reflected = {GetSum(QVector4D{0     ,  n.z(), -n.y(), n.x()} * eq_second),
                           GetSum(QVector4D{-n.z(),      0,  n.x(), n.y()} * eq_second),
                           GetSum(QVector4D{n.y() , -n.x(),      0, n.z()} * eq_second)};
    return reflected;
}

QVector4D GetPlaneEquation(const Polygon& p) {
    QVector4D result;
    QVector3D a = p[1].toVector3DAffine() - p[0].toVector3DAffine();
    QVector3D b = p[2].toVector3DAffine() - p[0].toVector3DAffine();
    result.setX(a.y() * b.z() - a.z() * b.y());
    result.setY(a.z() * b.x() - a.x() * b.z());
    result.setZ(a.x() * b.y() - a.y() * b.x());
    result.setW(- result.x() * p[0].x() - result.y() * p[0].y() - result.z() * p[0].z());
    return result;
}
