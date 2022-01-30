#include "transformer.h"

Transformer::Transformer(QObject* parent)
    : QObject(parent){}

Transformer& Transformer::resetMatrix() {
    translate_matrix = ZERO_MATRIX;
    scale_matrix = ONE_MATRIX;
    rotate_matrix = ONE_MATRIX;
    return *this;
}

Transformer& Transformer::setScale(double scale) {
    scale_matrix  =   {scale, 0, 0, 0,
                       0, scale, 0, 0,
                       0, 0, scale, 0,
                       0,   0,  0,  1};
    emit updated();
    return *this;
}

Transformer& Transformer::setTranslation(double x_t, double y_t, double z_t) {
    translate_matrix  =   {0,   0,   0,   0,
                           0,   0,   0,   0,
                           0,   0,   0,   0,
                           x_t, y_t, z_t, 0};
    emit updated();
    return *this;
}

Transformer& Transformer::setRotation(double x_d, double y_d, double z_d) {
    double x_teta = qDegreesToRadians(x_d);
    double y_teta = qDegreesToRadians(y_d);
    double z_teta = qDegreesToRadians(z_d);
    QMatrix4x4 rotate_x = {1,        0,        0,        0,
                           0,  cos(x_teta),-sin(x_teta), 0,
                           0,  sin(x_teta), cos(x_teta), 0,
                           0,        0,        0,        1};


    QMatrix4x4 rotate_y = {cos(y_teta), 0,  sin(y_teta), 0,
                           0,           1,      0,       0,
                           -sin(y_teta),0,  cos(y_teta), 0,
                           0,           0,      0,       1};

    QMatrix4x4 rotate_z = {cos(z_teta), -sin(z_teta),  0, 0,
                           sin(z_teta),  cos(z_teta),  0, 0,
                           0,            0,            1, 0,
                           0,            0,            0, 1};
    rotate_matrix = rotate_x * rotate_y * rotate_z;
    emit updated();
    return *this;
}

QMatrix4x4 Transformer::getTransformMatrix() {
    return (scale_matrix + translate_matrix) * rotate_matrix;
}

QVector<QVector4D> Transformer::transform(QVector<QVector4D> points) {
    QMatrix4x4 transform_matrix = getTransformMatrix();
    for (QVector4D& point : points) {
        point = point * transform_matrix;
    }
    return points;
}

QVector4D Transformer::transform(QVector4D point) {
    QMatrix4x4 transform_matrix = getTransformMatrix();
    return point * transform_matrix;
}
