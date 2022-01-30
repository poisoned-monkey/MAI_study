#include "pointtransformer.h"





PointTransformer::PointTransformer(QObject *parent)
    : QObject(parent) {}


void PointTransformer::SetEnabled(bool _enabled) {
    enabled = _enabled;
}

bool PointTransformer::IsEnabled() {
    return enabled;
}

QVector<Polygon> PointTransformer::Transform(QVector<Polygon> _polygons) {
    if (enabled) {
        return TransformImpl(std::move(_polygons));
    }
    return _polygons;
}
