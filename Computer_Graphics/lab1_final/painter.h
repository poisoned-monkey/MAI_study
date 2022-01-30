#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsView>

class Painter : public QGraphicsView
{
    Q_OBJECT
public:
    Painter(QWidget* parent = nullptr);
    
private:
    QSharedPointer<QGraphicsScene> scene;
};

#endif // PAINTER_H