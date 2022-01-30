#include "projecter.h"

Projecter::Projecter(PointTransformer* parent)
    : PointTransformer(parent) {}

void Projecter::SetPlaneY(double _y) {
    y = _y;
}

void Projecter::SetCam(QVector4D _cam) {
    cam = _cam;
}


QVector4D Projecter::TransformPoint(QVector4D point) {
    QVector3D affine_proj = cam.toVector3DAffine();
    QVector3D proj_vector = point.toVector3DAffine() - cam.toVector3DAffine();
    double x_intersection = (proj_vector.x() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.x();
    double z_intersection = (proj_vector.z() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.z();
    return{x_intersection,point.toVector3DAffine().y(),z_intersection,1};
}

Polygon Projecter::TransformImpl(Polygon _polygon) {
    for (QVector4D& v : _polygon) {
        QVector3D affine_proj = cam.toVector3DAffine();
        QVector3D proj_vector = v.toVector3DAffine() - cam.toVector3DAffine();
        double x_intersection = (proj_vector.x() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.x();
        double z_intersection = (proj_vector.z() * (y - affine_proj.y())) / proj_vector.y() + affine_proj.z();
        v = {x_intersection,v.toVector3DAffine().y(),z_intersection,1};
    }
    return _polygon;
}

QVector<Polygon> Projecter::TransformImpl(QVector<Polygon> _polygons) {
    for (Polygon& p : _polygons) {
        p = TransformImpl(std::move(p));
    }
    return _polygons;
}
