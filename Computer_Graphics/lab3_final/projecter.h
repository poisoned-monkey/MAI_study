#ifndef PROJECTER_H
#define PROJECTER_H

#include "pointtransformer.h"
#include "figure.h"
#include <QObject>
#include <QWidget>
#include <QVector4D>
#include <QVector3D>

class Projecter : public PointTransformer
{
    Q_OBJECT
public:
    Projecter(PointTransformer* parent = nullptr);

    void SetPlaneY(double _y);
    void SetCam(QVector4D _cam);
    QVector4D TransformPoint(QVector4D point);

private:
    Polygon TransformImpl(Polygon _polygons);
    QVector<Polygon> TransformImpl(QVector<Polygon> _polygons) override;

    double y = 0;
    QVector4D cam;


};

#endif // PROJECTER_H
