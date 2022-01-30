#include "painter.h"

Painter::Painter(QWidget* parent)
    : QGraphicsView(parent), scene(QSharedPointer<QGraphicsScene>::create(this)) {

}