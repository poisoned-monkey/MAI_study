#include "projecter.h"

Projecter::Projecter(QObject* parent)
    : QObject(parent) {}

Projecter& Projecter::setPlaneY(double _y) {
    y = _y;
    emit updated();
    return *this;
}

Projecter& Projecter::setCam(QVector4D _cam) {
    cam = _cam;
    emit updated();
    return *this;
}

QVector<QVector4D> Projecter::project(const QVector<QVector4D> &to_project) {
    QVector<QVector4D> result;
    for (const QVector4D& v : to_project) {
        QVector3D affine_proj = cam.toVector3DAffine();
        QVector3D proj_vector = v.toVector3DAffine() - cam.toVector3DAffine();
        double x_intersection = (proj_vector.x() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.x();
        double z_intersection = (proj_vector.z() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.z();
        result.push_back({x_intersection,v.toVector3DAffine().y(),z_intersection,1});
    }
    return result;
}

