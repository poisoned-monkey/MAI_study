#include "rasterizer.h"

Rasterizer::Rasterizer(QObject* parent)
    : QObject(parent) {}



QVector<RasterPolygon> Rasterizer::rasterize(const QVector<Polygon>& polygons) const {
    QVector<RasterPolygon> result;
    std::transform(polygons.begin(), polygons.end(), std::back_inserter(result), [] (const Polygon& p) {
        RasterPolygon rasterized;
        std::transform(p.begin(), p.end(), std::back_inserter(rasterized), [] (const QVector4D& v) {
            QVector3D affinized = v.toVector3DAffine();
            return QPointF(affinized.x(), -affinized.z());
        });
        return rasterized;
    });

    return result;
}


