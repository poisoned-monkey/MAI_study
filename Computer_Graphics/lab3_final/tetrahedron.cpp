#include "tetrahedron.h"

Tetrahedron::Tetrahedron(Figure* parent)
    : Figure(parent) {
    CalculatePoints();
}

void Tetrahedron::SetEdge(double _edge) {
    edge = _edge;
}

void Tetrahedron::CalculatePoints() {
    points.clear();
    double height = std::sqrt(2.0 / 3.0) * edge;
    points.push_back({0,0,height * (2.0/3.0),1});
    for (int i = 0; i < 3; ++i) {
        double angle = 2 * M_PI * (i / 3.0);
        double radius = edge / std::sqrt(3);
        points.push_back({std::sin(angle) * radius, std::cos(angle) * radius, -height / 3.0, 1});
    }
}


QVector<Polygon> Tetrahedron::GetPolygons()  {
    QVector<Polygon> result;
    CalculatePoints();
    result.push_back({points[0], points[1], points[2]});
    result.push_back({points[0], points[2], points[3]});
    result.push_back({points[0], points[1], points[3]});
    result.push_back({points[1], points[2], points[3]});
    return result;

}
