#include "Ellipsoid.h"

Ellipsoid::Ellipsoid(float _a, float _b, float _c, float _up_cut, float _down_cut, int _layers, int _points) {
    SetCutFactors(_up_cut, _down_cut);
    SetLayerCount(_layers);
    SetPointCount(_points);
    SetParams(_a,_b,_c);
    changed = false;
}

void Ellipsoid::SetCutFactors(float up, float down) {
    if (up == up_cut_factor && down == down_cut_factor) {
        return;
    }
    up_cut_factor = std::max(-1.f, std::min(1.f,up));
    down_cut_factor = std::max(-1.f, std::min(1.f,down));;
    if (down_cut_factor > up_cut_factor) {
        std::swap(down_cut_factor, up_cut_factor);
    }
    changed = true;
}

void Ellipsoid::SetParams(float _a, float _b, float _c) {
    if (a == _a && b == _b && c == _c) {
        return;
    }
    a = std::min(1.f, std::abs(_a));
    b = std::min(1.f, std::abs(_b));
    c = std::min(1.f, std::abs(_c));
    changed = true;
}

void Ellipsoid::SetPointCount(int _count) {
    if (point_count == _count) {
        return;
    }
    point_count = _count;
    changed = true;
}

void Ellipsoid::SetLayerCount(int _count) {
    if (layer_count == _count) {
        return;
    }
    layer_count = _count;
    changed = true;
}

void PushPointToVector(std::vector<float>& points, glm::vec3 p) {
    points.push_back(p.x);
    points.push_back(p.y);
    points.push_back(p.z);
}

bool Ellipsoid::isChanged() const {
    return changed;
}


std::vector<float> Ellipsoid::GetTriangles() const {
    changed = false;
    std::vector<glm::vec3> points = GetPoints();
    std::vector<float> triangles;
    int layer_recounted = layer_count;
    for (int i = 0; i < point_count; ++i) {
        glm::vec3 normal = {0,0,-1.f};//glm::triangleNormal(points[points.size() - 2], points[i], points[(i + 1) % layer_recounted]);

        PushPointToVector(triangles, points[points.size() - 2]);
        PushPointToVector(triangles, normal);
        PushPointToVector(triangles, points[i]);
        PushPointToVector(triangles, normal);
        PushPointToVector(triangles, points[(i + 1) % layer_recounted]);
        PushPointToVector(triangles, normal);

        PushPointToVector(triangles, points[points.size() - 1]);
        PushPointToVector(triangles, -normal);
        PushPointToVector(triangles, points[points.size() - 3 - i]);
        PushPointToVector(triangles, -normal);
        PushPointToVector(triangles, points[points.size() - 3 - ((i + 1) % layer_recounted)]);
        PushPointToVector(triangles, -normal);
    }
//    for (int i = 1; i < point_count - 1; ++i) {
//        glm::vec3 normal = {0,0,10};//glm::triangleNormal(points[points.size() - 2], points[i], points[(i + 1) % layer_recounted]);
//
//        PushPointToVector(triangles, points[0]);
//        PushPointToVector(triangles, -normal);
//        PushPointToVector(triangles, points[i]);
//        PushPointToVector(triangles, -normal);
//        PushPointToVector(triangles, points[(i + 1) % layer_recounted]);
//        PushPointToVector(triangles, -normal);
//
//        PushPointToVector(triangles, points[points.size() - 3]);
//        PushPointToVector(triangles, normal);
//        PushPointToVector(triangles, points[points.size() - 3 - i]);
//        PushPointToVector(triangles, normal);
//        PushPointToVector(triangles, points[points.size() - 3 - ((i + 1) % layer_recounted)]);
//        PushPointToVector(triangles, normal);
//    }

    for (int i = 0; i < layer_recounted - 1; ++i) {
        for (int j = 0; j < point_count; ++j) {
            glm::vec3 normal = glm::triangleNormal(points[j + point_count * i], points[(j + 1) % point_count + point_count * i], points[(j + 1) % point_count + point_count * (i + 1)]);

            PushPointToVector(triangles, points[j + point_count * i]);
            PushPointToVector(triangles, normal);
            PushPointToVector(triangles, points[(j + 1) % point_count + point_count * i]);
            PushPointToVector(triangles, normal);
            PushPointToVector(triangles, points[(j + 1) % point_count + point_count * (i + 1)]);
            PushPointToVector(triangles, normal);

            PushPointToVector(triangles, points[(j + 1) % point_count + point_count * (i + 1)]);
            PushPointToVector(triangles, normal);
            PushPointToVector(triangles, points[j + point_count * (i + 1)]);
            PushPointToVector(triangles, normal);
            PushPointToVector(triangles, points[j + point_count * i]);
            PushPointToVector(triangles, normal);
        }
    }
    return triangles;
}


std::vector<glm::vec3> Ellipsoid::GetPoints() const {
    std::vector<glm::vec3> points;
    double upper_angle = up_cut_factor * M_PI / 2.0 + M_PI_2;
    double lower_angle = down_cut_factor * M_PI / 2.0 + M_PI_2;
    int layer_recounted = layer_count;
    double step = (upper_angle - lower_angle) / (layer_recounted + 1);
    double max_z = c * std::cos(upper_angle - step);
    double min_z = c * std::cos(upper_angle - layer_recounted * step);
    double mid_z = (max_z + min_z) / 2;
    glm::vec3 upper_point;
    glm::vec3 lower_point;
    for (int i = 1; i <= layer_recounted; ++i) {
        double teta = upper_angle - i * step;
        double z = c * std::cos(teta);
        if (i == 1) {
            upper_point = {0, 0, z - mid_z};
        }
        if (i == layer_recounted) {
            lower_point = {0, 0, z - mid_z};
        }
        for (int j = 0; j < point_count; ++j) {
            double fi = 2 * M_PI * j / point_count;
            double x = a * std::sin(teta) * std::cos(fi);
            double y = b * std::sin(teta) * std::sin(fi);
            points.push_back({x, y, z - mid_z});
        }

    }
    points.push_back(upper_point);
    points.push_back(lower_point);
    return points;
}