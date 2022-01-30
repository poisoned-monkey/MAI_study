#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <iostream>
#include <QtMath>
#include <QTransform>
#include <QMatrix4x4>
#include <stdexcept>
#include <QHash>
#include <QWheelEvent>
#include <QPainter>
#include <cmath>
#include "functionapproximizer.h"

struct WidgetParameters {
    long long n;
    double a,B;
    long long x_t = 0, y_t = 0;
    double scale = 1;
    int r;
};

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    GraphicWidget(QWidget* parent = 0);

public slots:
    void SetParameters(QHash<QString, double>);

protected:
    virtual void paintEvent(QPaintEvent* e) override;
    virtual void wheelEvent(QWheelEvent* e) override;
    virtual void mouseMoveEvent(QMouseEvent* e) override;
    virtual void mousePressEvent(QMouseEvent* e) override;


private:
    void PaintAxis(QPainter& ptr, QPen& pen);

    WidgetParameters params = {100,100,100,0,0,10,0};
    FunctionApproximizer appr;
    int prev_x, prev_y;
};

#endif // GRAPHICWIDGET_H