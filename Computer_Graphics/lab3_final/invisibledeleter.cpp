#include "invisibledeleter.h"

InvisibleDeleter::InvisibleDeleter(PointTransformer* parent)
    : PointTransformer(parent) {}


void InvisibleDeleter::SetViewPoint(QVector4D _position) {
    position = _position;
}

void InvisibleDeleter::SetCheckPoint(QVector4D _point) {
    check_point = _point;
}


QVector<Polygon> InvisibleDeleter::TransformImpl(QVector<Polygon> polygons) {
    auto it = std::remove_if(polygons.begin(), polygons.end(), [this] (const Polygon& polygon) {
        QVector4D normal_vector = polygon.GetNormal(check_point);
        QVector4D view_res = position * normal_vector;
        double sum_view = view_res.x() + view_res.y() + view_res.z();
        return sum_view <= 0;
    });
    polygons.erase(it, polygons.end());
    return polygons;
}
