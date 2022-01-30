#include "square.h"

Square::Square(double _size)
    : size(_size){
    calculatePoints();
}


Square::Square(Figure* parent)
    : Figure(parent){
    calculatePoints();
}

void Square::calculatePoints() {
    figure_points.clear();
    figure_points.reserve(Square::POINT_COUNT * 2);
    auto nth_bit = [] (int n, int bit) -> double {return ((n >> bit) & 1) == 0 ? -1 : 1;};
    for (int i = 0; i < 8; ++i) {
        figure_points.push_back({nth_bit(i,0) * size, nth_bit(i,1) * size, nth_bit(i,2) * size, 1});
    }
    std::swap(figure_points[2], figure_points[3]);
    std::swap(figure_points[2 + Square::POINT_COUNT], figure_points[3 + Square::POINT_COUNT]);
}

void Square::producePolygons() { // work only with transformed points
    QVector<Polygon> result;
    for (int i = 0; i < POINT_COUNT; ++i) {
        result.push_back({projected_points[i], projected_points[(i + 1) % POINT_COUNT], projected_points[(i + 1) % POINT_COUNT + POINT_COUNT], projected_points[i + POINT_COUNT]});
    }

    Polygon upper;
    Polygon lower;
    for (int i = 0; i < POINT_COUNT; ++i) {
        upper.push_back(projected_points[i]);
        lower.push_back(projected_points[i + POINT_COUNT]);
    }
    result.push_back(upper);
    result.push_back(lower);

    polygons = std::move(result);
}

