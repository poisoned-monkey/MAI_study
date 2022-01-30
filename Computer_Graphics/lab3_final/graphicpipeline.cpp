#include "graphicpipeline.h"

GraphicPipeline::GraphicPipeline(QObject* parent)
    : QObject(nullptr) {}

QVector<Polygon> GraphicPipeline::Process(Figure* fig) {
    QVector<Polygon> polygons = fig->GetPolygons();
    return Process(std::move(polygons));
}

QVector<Polygon> GraphicPipeline::Process(QVector<Polygon> polygons) {
    for (PointTransformer* ptr : pipe_elements) {
        polygons = ptr->Transform(std::move(polygons));
    }
    return polygons;
}

void GraphicPipeline::AddTransformer(PointTransformer* new_tr) {
    pipe_elements.push_back(new_tr);
}
