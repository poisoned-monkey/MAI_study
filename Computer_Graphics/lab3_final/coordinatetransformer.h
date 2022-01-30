#ifndef COORDINATETRANSFORMER_H
#define COORDINATETRANSFORMER_H


#include <QObject>
#include <QWidget>
#include <QtMath>
#include <QMatrix4x4>
#include "pointtransformer.h"

#define ONE_MATRIX {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define ZERO_MATRIX {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

class CoordinateTransformer : public PointTransformer
{
    Q_OBJECT
public:
    CoordinateTransformer(PointTransformer* parent = nullptr);

    void SetScale(double scale);
    void SetTranslation(double x_t, double y_t, double z_t);
    void SetRotation(double x_d, double y_d, double z_d);

    QVector4D TransformPoint(QVector4D point);


private:

    Polygon TransformImpl(Polygon polygon);
    QVector<Polygon> TransformImpl(QVector<Polygon> polygons) override;

    QMatrix4x4 GetTransformMatrix();

    QMatrix4x4 transform_matrix;
    QMatrix4x4 translate_matrix = ZERO_MATRIX;
    QMatrix4x4 scale_matrix = ONE_MATRIX;
    QMatrix4x4 rotate_matrix = ONE_MATRIX;
};

#endif // COORDINATETRANSFORMER_H
