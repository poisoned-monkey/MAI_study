#include "Surface.h"

Surface::Surface(std::vector<glm::vec3> curve1, std::vector<glm::vec3> curve2)
    : first_curve(std::move(curve1)), second_curve(std::move(curve2)) {
    RecalculatePoints();
}

const Bezier& Surface::GetSecondCurve() const {
    return second_curve;
}

Bezier& Surface::GetFirstCurve() {
    return first_curve;
}

const Bezier& Surface::GetFirstCurve() const {
    return first_curve;
}

Bezier& Surface::GetSecondCurve() {
    return second_curve;
}

bool Surface::isChanged() {
    return changed || first_curve.isChanged() || second_curve.isChanged();
}

void Surface::SetPrecision(size_t p) {
    if (p == precision) {
        return;
    }
    changed = true;
    precision = p;
    first_curve.SetPrecision(p);
    second_curve.SetPrecision(p);
}



void Surface::RecalculatePoints() const {
    if (!first_curve.isChanged() && !second_curve.isChanged() && !changed) {
        return;
    }

    const std::vector<glm::vec3>& first_curve_points = first_curve.GetPoints();
    const std::vector<glm::vec3>& second_curve_points = second_curve.GetPoints();

    surface_points.clear();
    for(int i = 0; i < first_curve_points.size(); ++i) {
        for (int j = 0; j < precision; ++j) {
            glm::vec3 p1 = first_curve_points[i];
            glm::vec3 p2 = second_curve_points[i];
            double v = j * (1 / double(precision - 1));
            surface_points.push_back(p1 * float(1 - v) + p2 * float(v));
        }
    }
    changed = false;
}

void PushPointToVector(std::vector<float>& v, glm::vec3 p) {
    v.push_back(p.x);
    v.push_back(p.y);
    v.push_back(p.z);
}

std::vector<float> Surface::GetTriangles() const {
    RecalculatePoints();
    std::vector<float> result;
    for (int i = 0; i < precision - 1; ++i) {
        for (int j = 0; j < precision - 1; ++j) {
            glm::vec3 p1 = surface_points[precision * i + j];
            glm::vec3 p2 = surface_points[precision * i + j + 1];
            glm::vec3 p3 = surface_points[precision * (i + 1) + j + 1];
            glm::vec3 p4 = surface_points[precision * (i + 1) + j];

            glm::vec3 normal = glm::triangleNormal(p1,p2,p3);

            PushPointToVector(result, p1);
            PushPointToVector(result, normal);
            PushPointToVector(result, p2);
            PushPointToVector(result, normal);
            PushPointToVector(result, p3);
            PushPointToVector(result, normal);

            PushPointToVector(result, p3);
            PushPointToVector(result, normal);
            PushPointToVector(result, p4);
            PushPointToVector(result, normal);
            PushPointToVector(result, p1);
            PushPointToVector(result, normal);

        }
    }

    return result;
}

std::vector<glm::vec3> Surface::GetPoints() const {
    if (!first_curve.isChanged() && !second_curve.isChanged() && !changed) {
        return surface_points;
    }
    RecalculatePoints();
    return surface_points;
}