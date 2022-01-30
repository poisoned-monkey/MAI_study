#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "pointtransformer.h"
#include <algorithm>
#include <QObject>
#include <QWidget>

class Rasterizer : public PointTransformer
{
public:
    Rasterizer(PointTransformer* parent = nullptr);

private:
    Polygon TransformImpl(Polygon p);
    QVector<Polygon> TransformImpl(QVector<Polygon>) override;

};

#endif // RASTERIZER_H
