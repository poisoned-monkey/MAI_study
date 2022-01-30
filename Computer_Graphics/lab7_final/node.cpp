#include "node.h"

Node::Node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem(x, y, width, height, parent) {}

Node::Node(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent) {}

Node::Node(QGraphicsItem *parent)
    : QGraphicsRectItem(parent) {}

void Node::setIndex(int _index) {
    index = _index;
}

void Node::setView(GraphicWidget* _view) {
    view = _view;
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionChange && scene()) {
        view->Update(index, value.toPointF());
        return QGraphicsRectItem::itemChange(change, value);
    }
    return QGraphicsRectItem::itemChange(change, value);
}
