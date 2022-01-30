#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "graphicwidget.h"

class GraphicWidget;

class Node : public QGraphicsRectItem
{
public:
    Node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    Node(const QRectF &rect, QGraphicsItem *parent = nullptr);
    Node(QGraphicsItem *parent = nullptr);

    void setIndex(int index);
    void setView(GraphicWidget* view);

private:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    
    int index = 0;
    GraphicWidget* view = nullptr;

};

#endif // NODE_H
