#include "coordinatetransformer.h"

CoordinateTransformer::CoordinateTransformer(PointTransformer* parent)
    : PointTransformer(parent) {}

void CoordinateTransformer::SetScale(double scale) {
    scale_matrix  =   {scale, 0, 0, 0,
                       0, scale, 0, 0,
                       0, 0, scale, 0,
                       0,   0,  0,  1};
}

void CoordinateTransformer::SetTranslation(double x_t, double y_t, double z_t) {
    translate_matrix  =   {0,   0,   0,   0,
                           0,   0,   0,   0,
                           0,   0,   0,   0,
                           x_t, y_t, z_t, 0};
}

QVector4D CoordinateTransformer::TransformPoint(QVector4D point) {
    transform_matrix = GetTransformMatrix();
    return point * transform_matrix;
}

void CoordinateTransformer::SetRotation(double x_d, double y_d, double z_d) {
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
}

QMatrix4x4 CoordinateTransformer::GetTransformMatrix() {
    return (scale_matrix + translate_matrix) * rotate_matrix;
}

Polygon CoordinateTransformer::TransformImpl(Polygon polygon) {
    for (QVector4D& point : polygon) {
        point = (point * transform_matrix);
    }
    return polygon;
}

QVector<Polygon> CoordinateTransformer::TransformImpl(QVector<Polygon> polygons) {
    transform_matrix = GetTransformMatrix();
    for (Polygon& polygon : polygons) {
        polygon = TransformImpl(std::move(polygon));
    }
    return polygons;
}
