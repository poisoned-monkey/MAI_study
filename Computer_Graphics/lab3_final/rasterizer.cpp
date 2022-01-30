#include "rasterizer.h"

Rasterizer::Rasterizer(PointTransformer* parent)
    : PointTransformer(parent) {}


Polygon Rasterizer::TransformImpl(Polygon p) {
    std::for_each(p.begin(), p.end(), [] (QVector4D& v) {
        v = QVector4D{v.x() / v.w(), -v.z() / v.w(), 0, 0};
    });
    return p;
}

QVector<Polygon> Rasterizer::TransformImpl(QVector<Polygon> _polygons) {
    for (Polygon& p : _polygons) {
        p = TransformImpl(std::move(p));
    }
    return _polygons;
}
