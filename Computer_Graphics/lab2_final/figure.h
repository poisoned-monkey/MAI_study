#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QVector3D>
#include <QPainter>
#include <QVector>
#include <stdexcept>
#include "rasterizer.h"
#include "projecter.h"
#include "transformer.h"
#include "invisibledeleter.h"


class Figure : public QObject
{
    Q_OBJECT
public:
    Figure(QObject* parent = nullptr);
    void paint(QPainter* ptr);
    Figure& setRasterizer(Rasterizer* _rasterizer);
    Figure& setProjecter(Projecter* _projecter);
    Figure& setTransformer(Transformer* _transformer);
    Figure& setInvisibleDeleter(InvisibleDeleter* _deleter);
    virtual ~Figure();

public slots:

    void transformerUpdated();
    void projecterUpdated();

protected:

    void updatePoints();
    void drawFigure(QPainter* ptr);
    virtual void producePolygons() = 0;
    void updateRasterizedPoints();
    void updateVisiblePoints();
    void updateTransformedPoints();
    void updateProjectedPoints();

    Rasterizer* rasterizer = nullptr;
    InvisibleDeleter* deleter = nullptr;
    Transformer* transformer = nullptr;
    Projecter* projecter = nullptr;

    QVector<QVector4D> figure_points; //figure
    QVector<QVector4D> transformed_points; // rotate and scale
    QVector<QVector4D> projected_points; // project to plane
    QVector<Polygon> polygons;
    QVector<Polygon> visible_polygons;
    QVector<RasterPolygon> rasterized_polygons;

    bool transformer_changed = true;
    bool projecter_changed = true;
};

#endif // POINTGENERATOR_H
