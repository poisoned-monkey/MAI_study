#ifndef POINTTRANSFORMER_H
#define POINTTRANSFORMER_H

#include <QObject>
#include "figure.h"
#include <QVector3D>





class PointTransformer : public QObject
{
    Q_OBJECT
public:
    explicit PointTransformer(QObject *parent = nullptr);


    void SetEnabled(bool _enabled);
    bool IsEnabled();


    QVector<Polygon> Transform(QVector<Polygon>);

protected:

    virtual QVector<Polygon> TransformImpl(QVector<Polygon>) = 0;


    bool enabled = true;

};

#endif // POINTTRANSFORMER_H
