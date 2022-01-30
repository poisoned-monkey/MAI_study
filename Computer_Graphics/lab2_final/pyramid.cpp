#include "pyramid.h"

Pyramid::Pyramid(Figure* parent)
    : Figure(parent) {}

Pyramid::Pyramid(double _height, double _lower_radius, double _upper_radius)
    : height(_height), lower_radius(_lower_radius), upper_radius(_upper_radius) {
    calculatePoints();
}

void Pyramid::changeParameters(double _height, double _lower_radius, double _upper_radius) {
    if (height == _height && lower_radius == _lower_radius && upper_radius == _upper_radius) {
        return;
    }
    height = _height;
    lower_radius = _lower_radius;
    upper_radius = _upper_radius;
    calculatePoints();
}

void Pyramid::calculatePoints() {
    projecter_changed = true;
    transformer_changed = true;
    figure_points.resize(0);
    figure_points.reserve(Pyramid::POINT_COUNT * 2);
    for (int i = 0; i < Pyramid::POINT_COUNT; ++i) {
        double angle = 2 * M_PI * i / double(Pyramid::POINT_COUNT);
        figure_points.push_back({upper_radius * sin(angle), upper_radius * cos(angle), height / 2,1});
    }
    for (int i = 0; i < Pyramid::POINT_COUNT; ++i) {
        double angle = 2 * M_PI * i / double(Pyramid::POINT_COUNT);
        figure_points.push_back({lower_radius * sin(angle), lower_radius * cos(angle), -height / 2,1});
    }
}

void Pyramid::producePolygons() {
    polygons.clear();
    for (int i = 0; i < Pyramid::POINT_COUNT; ++i) {
        QVector4D a = projected_points[i];
        QVector4D b = projected_points[(i + 1) % Pyramid::POINT_COUNT];
        QVector4D c = projected_points[(i + 1) % Pyramid::POINT_COUNT + Pyramid::POINT_COUNT];
        QVector4D d = projected_points[i + Pyramid::POINT_COUNT];
        polygons.push_back({a,b,c,d});
    }

    Polygon upper;
    Polygon lower;
    for (int i = 0; i < Pyramid::POINT_COUNT; ++i) {
        upper.push_back(projected_points[i]);
        lower.push_back(projected_points[i + POINT_COUNT]);
    }
    std::reverse(upper.begin(),upper.end());
    polygons.push_back(upper);
    polygons.push_back(lower);
}

