#include "graphicwidget.h"

GraphicWidget::GraphicWidget(QWidget* parent)
    : QGraphicsView(parent) {
    Setup();
}


GraphicWidget::~GraphicWidget() {
    delete scene;
    delete nurb;
}

void GraphicWidget::setNodeSize(size_t size) {
    node_size = size;
}

//void GraphicWidget::mouseReleaseEvent(QMouseEvent* event) {

//}

//void GraphicWidget::mousePressEvent(QMouseEvent* event) {
//    map
//}

//void GraphicWidget::mouseMoveEvent(QMouseEvent *event) {
//    if (event->button() != Qt::LeftButton) {
//        return;
//    }
//}


void GraphicWidget::AddNode(QPointF scenePosition) {
    Node* item = new Node(-node_size / 2, -node_size / 2, node_size, node_size);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    item->setPos(scenePosition);
    item->setZValue(10);
    item->setIndex(items.size());
    item->setBrush(Qt::red);
    item->setView(this);
    scene->addItem(item);
    items.append(item);
}

void GraphicWidget::Update(int index, QPointF position) {
    QVector<QPainterPath> curve_part = nurb->UpdateNthPoint(index, position);
    for (int i = index; i < index + nurb_k; ++i) {
        curve[i]->setPath(curve_part[i - index]);
    }
    //std::cout << "Updated" << std::endl;
    show();
}

void GraphicWidget::UpdateAll() {
    QVector<QPainterPath> paths = nurb->GetAll();
    for (int i = 0; i < curve.size(); ++i) {
        scene->removeItem(curve[i]);
        delete curve[i];
        curve[i] = scene->addPath(paths[i]);
    }
    show();
}

void GraphicWidget::SetParams(QVector<double> _weights) {
    nurb->SetWeights(_weights);
    std::cout << "weights ";
    for (auto d : _weights) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    UpdateAll();
}

void GraphicWidget::Setup() {

    scene = new QGraphicsScene;
    scene->setSceneRect(-width() / 2,-height() / 2,width() / 2,height() / 2);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

//    int r = 60;
//    double step = M_PI / 3;
//    for (int i = 0; i < 6; ++i) {
//        AddNode(QPointF(r * std::cos(i * step), r * std::sin(i * step)));
//    }

    AddNode({-300, 100});
    AddNode({-200, 100});
    AddNode({-200, -200});
    AddNode({0, 100});
    AddNode({100, 0});
    AddNode({200, 100});

    QVector<QPointF> to_nurb;
    for (QGraphicsItem* item : items) {
        to_nurb.push_back(item->scenePos());
    }

    nurb = new NURBEstimator(to_nurb, nurb_k, 0.1);
    QVector<QPainterPath> paths = nurb->GetAll();
    for (const QPainterPath& p : paths) {
        curve.push_back(scene->addPath(p));
    }

    show();

}
