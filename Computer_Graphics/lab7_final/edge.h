#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsPathItem>

class Edge : public QGraphicsPathItem
{
public:
    Edge(const QPainterPath& path, QGraphicsItem* parent = nullptr);
    Edge(QGraphicsItem* parent = nullptr);



};

#endif // EDGE_H
