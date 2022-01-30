#include "invisibledeleter.h"




InvisibleDeleter::InvisibleDeleter(QObject* parent)
    : QObject(parent) {}


InvisibleDeleter::InvisibleDeleter(QVector4D _position)
    : position(_position){}

void InvisibleDeleter::setViewPoint(QVector4D _position) {
    position = _position;
}

QVector<Polygon> InvisibleDeleter::deleteInvisible(QVector<Polygon> polygons) {
    QVector<QVector4D> equations;
    QVector<Polygon> result;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(equations),
                   [] (const Polygon& p) {
                        return InvisibleDeleter::getPlaneEquation(p);
                   });
    for (int i = 0; i < equations.size(); ++i) {
        QVector4D view_res = position * equations[i];
        double sum_view = view_res.x() + view_res.y() + view_res.z() + view_res.w();
        if (sum_view < 0) {
            result.push_back(polygons[i]);
        }
    }
    return result;
}


QVector4D InvisibleDeleter::getPlaneEquation(Polygon p) {
    QVector4D result;
    QVector3D a = p[1].toVector3D() - p[0].toVector3D();
    QVector3D b = p[2].toVector3D() - p[0].toVector3D();
    result.setX(a.y() * b.z() - a.z() * b.y());
    result.setY(a.z() * b.x() - a.x() * b.z());
    result.setZ(a.x() * b.y() - a.y() * b.x());
    result.setW(-result.x() * p[0].x() - result.y() * p[0].y() - result.z() * p[0].z());
    return result;
}
