#include "Bezier.h"

const std::vector<glm::vec3>& Bezier::GetPoints() const {
    if (!changed) {
        return points;
    }
    points.resize(0);
    double step = 1 / double(precision - 1);
    int n = key_points.size() - 1;
    for (int k = 0; k < precision; ++k) {
        glm::vec3 cur_point = {0,0,0};
        for (int i = 0; i < key_points.size(); ++i) {
            cur_point += float(J(k * step, n, i)) * key_points[i];
        }
        points.push_back(cur_point);
    }
    return points;
}

const std::vector<glm::vec3>& Bezier::GetKeyPoints() const {
    return key_points;
}

bool Bezier::isChanged() const {
    return changed;
}

void Bezier::setChanged(bool change) {
    changed = change;
}

void Bezier::SetPrecision(size_t p) {
    changed = true;
    precision = p;
}


Bezier::Bezier(std::vector<glm::vec3> points)
    : key_points(std::move(points)) {}

void Bezier::AppendPoint(glm::vec3 point) {
    changed = true;
    key_points.push_back(point);
}

void Bezier::UpdatePoint(size_t index, glm::vec3 point) {
    changed = true;
    if (index >= key_points.size()) {
        throw std::out_of_range("Bezer point incorrect update");
    }
    key_points[index] = point;
}


void Bezier::UpdatePointVector(std::vector<glm::vec3> points) {
    changed = true;
    key_points = std::move(points);
}

double Bezier::J(double t, int n, int i) {
    return double(factorial(n) / (factorial(i) * factorial(n - i))) * std::pow(t,i) * std::pow(1 - t, n - i);
}