#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>
#include <QWidget>
#include <QtMath>
#include <QMatrix4x4>

#define ONE_MATRIX {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}
#define ZERO_MATRIX {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

class Transformer : public QObject
{
    Q_OBJECT
public:

    Transformer(QObject* parent = nullptr);

    Transformer& resetMatrix();
    Transformer& setScale(double scale);
    Transformer& setTranslation(double x_t, double y_t, double z_t);
    Transformer& setRotation(double x_d, double y_d, double z_d);

    QVector4D transform(QVector4D);
    QVector<QVector4D> transform(QVector<QVector4D> points);


signals:

    void updated();

private:

    QMatrix4x4 getTransformMatrix();

    QMatrix4x4 translate_matrix = ZERO_MATRIX;

    QMatrix4x4 scale_matrix = ONE_MATRIX;

    QMatrix4x4 rotate_matrix = ONE_MATRIX;

};

#endif // TRANSFORMER_H
