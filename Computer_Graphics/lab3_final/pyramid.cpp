#include "pyramid.h"




Pyramid::Pyramid(Figure* parent)
    : Figure(parent) {
    CalculatePoints();
}

void Pyramid::SetHeight(double _height) {
    height = _height;
}

void Pyramid::SetLowerRadius(double _lower) {
    lower_radius = _lower;
}

void Pyramid::SetUpperRadius(double _upper) {
    upper_radius = _upper;
}

void Pyramid::SetEdgeCount(int _count) {
    edge_count = _count;
}


QVector4D Pyramid::GetInnerPoint()  {
    return {0,0,0,1};
}

void Pyramid::CalculatePoints() {
    points.clear();
    points.reserve(edge_count * 2);
    for (int i = 0; i < edge_count; ++i) {
        double angle = 2 * M_PI * i / double(edge_count);
        points.push_back({upper_radius * sin(angle), upper_radius * cos(angle), height / 2,1});
    }
    for (int i = 0; i < edge_count; ++i) {
        double angle = 2 * M_PI * i / double(edge_count);
        points.push_back({lower_radius * sin(angle), lower_radius * cos(angle), -height / 2,1});
    }
}

QVector<Polygon> Pyramid::GetPolygons() {
    CalculatePoints();
    QVector<Polygon> polygons;
    for (int i = 0; i < edge_count; ++i) {
        QVector4D a = points[i];
        QVector4D b = points[(i + 1) % edge_count];
        QVector4D c = points[(i + 1) % edge_count + edge_count];
        QVector4D d = points[i + edge_count];
        polygons.push_back({a,b,c,d});
    }

    Polygon upper;
    Polygon lower;
    for (int i = 0; i < edge_count; ++i) {
        upper.push_back(points[i]);
        lower.push_back(points[i + edge_count]);

    }
    polygons.push_back(upper);
    polygons.push_back(lower);
    return polygons;
}

