#ifndef GRAPHICPIPELINE_H
#define GRAPHICPIPELINE_H

#include <QObject>
#include <QWidget>
#include <QSharedPointer>
#include "figure.h"
#include "pointtransformer.h"

class GraphicPipeline : QObject
{
    Q_OBJECT
public:
    GraphicPipeline(QObject* parent = nullptr);

    QVector<Polygon> Process(Figure* fig);
    QVector<Polygon> Process(QVector<Polygon> polygons);
    void AddTransformer(PointTransformer* new_tr);


private:
    QVector<PointTransformer*> pipe_elements;
};

#endif // GRAPHICPIPELINE_H
