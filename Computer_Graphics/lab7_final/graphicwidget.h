#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QObject>
#include <QGraphicsItem>
#include <QList>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QMouseEvent>
#include <cmath>
#include "node.h"
#include <iostream>

#include "nurbestimator.h"


class Node;

class GraphicWidget : public QGraphicsView
{
    Q_OBJECT

    friend Node;

public:
    GraphicWidget(QWidget* parent = nullptr);
    GraphicWidget(QGraphicsScene* scene, QWidget* parent = nullptr);

    ~GraphicWidget();

    void setNodeSize(size_t size);


public slots:
    void SetParams(QVector<double>);

protected:
//    virtual void mouseReleaseEvent(QMouseEvent* event) overri
//    virtual void mouseMoveEvent(QMouseEvent* event) override;
//    virtual void mousePressEvent(QMouseEvent* event) override;



private:



    void AddNode(QPointF scenePosition);
    void Setup();
    void Update(int index, QPointF position);
    void UpdateAll();

    NURBEstimator* nurb = nullptr;
    int nurb_k = 4;
    QVector<double> weights;

    int node_size = 20;


    QGraphicsScene* scene = nullptr;
    QVector<QGraphicsItem*> items;
    QVector<QGraphicsPathItem*> curve;
};

#endif // GRAPHICWIDGET_H
