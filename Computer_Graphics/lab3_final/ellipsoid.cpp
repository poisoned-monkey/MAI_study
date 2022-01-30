#include "ellipsoid.h"

Ellipsoid::Ellipsoid(Figure* parent)
    : Figure(parent) {}


void Ellipsoid::SetLayersCount(int _count) {
    layers_count = _count;
    changed = true;
}

void Ellipsoid::SetPointsCount(int _count) {
    layer_points_count = _count;
    changed = true;
}

void Ellipsoid::SetEllipsoidCoefs(double _a, double _b, double _c) {
    a = _a;
    b = _b;
    c = _c;
    changed = true;
}

void Ellipsoid::SetTruncCoefs(double _upper, double _lower) {
    if (_upper < _lower) {
        std::swap(_upper, _lower);
    }
    upper_trunc = _upper;
    lower_trunc = _lower;
    changed = true;
}



QVector<Polygon> Ellipsoid::GetPolygons() {
    if (!changed && !polygon_cache.empty()) {
        return polygon_cache;
    }
    CalculatePoints();
    QVector<Polygon> result;
//    Polygon upper;
//    Polygon lower;
    for (int i = 0; i < layer_points_count; ++i) {
        result.push_back({points[points.size() - 2], points[i], points[(i + 1) % layer_points_count]});
        result.push_back({points[points.size() - 1], points[points.size() - 3 - i], points[points.size() - 3 - ((i + 1) % layer_points_count)]});
    }
//    result.push_back(upper);
//    result.push_back(lower);
    for (int i = 0; i < layers_count - 1; ++i) {
        for (int j = 0; j < layer_points_count; ++j) {
            result.push_back({points[j + layer_points_count * i],
                              points[(j + 1) % layer_points_count + layer_points_count * i],
                              points[(j + 1) % layer_points_count + layer_points_count * (i + 1)],
                              points[j + layer_points_count * (i + 1)]});

        }
    }
    if (polygon_cache.empty() || changed) {
        polygon_cache = result;
        changed = false;
    }
    return result;
}

void Ellipsoid::CalculatePoints() {
    points.clear();
    double upper_angle = upper_trunc * M_PI / 2.0 + M_PI_2;
    double lower_angle = lower_trunc * M_PI / 2.0 + M_PI_2;
    double step = (upper_angle - lower_angle) / (layers_count + 1);
    double max_z = c * std::cos(upper_angle - step);
    double min_z = c * std::cos(upper_angle - layers_count * step);
    double mid_z = (max_z + min_z) / 2;
    QVector4D upper_point;
    QVector4D lower_point;
    for (int i = 1; i <= layers_count; ++i) {
        double teta = upper_angle - i * step;
        double z = c * std::cos(teta);
        if (i == 1) {
            upper_point = {0,0,z - mid_z,1};
        }
        if (i == layers_count) {
            lower_point = {0,0,z - mid_z,1};
        }
        for (int j = 0; j < layer_points_count; ++j) {
            double fi = 2 * M_PI * j / layer_points_count;
            double x = a * std::sin(teta) * std::cos(fi);
            double y = b * std::sin(teta) * std::sin(fi);
            points.push_back({x,y,z - mid_z,1});
        }

    }
    points.push_back(upper_point);
    points.push_back(lower_point);
}


QVector4D Ellipsoid::GetInnerPoint() {
//    double upper_angle = upper_trunc * M_PI / 2.0 + M_PI_2;
//    double lower_angle = lower_trunc * M_PI / 2.0 + M_PI_2;
//    double step = (upper_angle - lower_angle) / (layers_count + 1);

//    return {0,0,(min_z + max_z) / 2,1};
    return {0,0,0,1};
}
