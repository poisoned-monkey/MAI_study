#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QVector4D>
#include <QVector3D>
#include <QVector>
#include <QPointF>
#include <algorithm>

using Polygon = QVector<QVector4D>;
using RasterPolygon = QVector<QPointF>;

enum class RasterizerMode {
    Perspective,
    Parallel
};

class Rasterizer : public QObject
{
    Q_OBJECT
public:
    
    Rasterizer(QObject* parent = nullptr);
    

    QVector<RasterPolygon> rasterize(const QVector<Polygon>& points) const;
    //QVector<QPointF> rasterize(const QVector<QVector4D>& points) const;

    
};

#endif // RASTERIZER_H
