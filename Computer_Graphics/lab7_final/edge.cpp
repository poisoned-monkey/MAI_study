#include "edge.h"

Edge(const QPainterPath& path, QGraphicsItem* parent)
    : QGraphicsPathItem(path, parent) {}

Edge(QGraphicsItem* parent)
    : QGraphicsPathItem(parent) {}
