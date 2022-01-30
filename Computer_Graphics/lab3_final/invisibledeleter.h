#ifndef INVISIBLEDELETER_H
#define INVISIBLEDELETER_H

#include "pointtransformer.h"
#include <QObject>
#include <QVector3D>
#include <QVector4D>
#include <algorithm>
#include <QWidget>


template <typename T>
int sign(T e) {
    return e > 0 ? 1 : (e < 0 ? -1 : 0);
}

class InvisibleDeleter : public PointTransformer
{
    Q_OBJECT
public:
    InvisibleDeleter(PointTransformer* parent = nullptr);

    void SetViewPoint(QVector4D _position);
    void SetCheckPoint(QVector4D _point);
    
private:
    
    QVector<Polygon> TransformImpl(QVector<Polygon> polygons) override;
    QVector4D position;
    QVector4D check_point = {0,0,0,1};
};

#endif // INVISIBLEDELETER_H
