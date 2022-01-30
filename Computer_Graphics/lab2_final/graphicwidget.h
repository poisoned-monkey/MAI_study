#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QSharedPointer>
#include <QHash>
#include "figure.h"
#include "pyramid.h"
#include "transformer.h"
#include "rasterizer.h"
#include "square.h"
#include "projecter.h"
#include "invisibledeleter.h"

struct GraphicParameters {
    double x_d;
    double y_d;
    double z_d;
    double u_r;
    double l_r;
    double height;
    double scale;
    bool perspective;
    bool del_inv;
};

std::ostream& operator << (std::ostream& os, const GraphicParameters& params);

class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    GraphicWidget(QWidget* parent = 0);
    virtual void paintEvent(QPaintEvent* e) override;

public slots:
    void SetParameters(QHash<QString, double>);



private:
    GraphicParameters params;
    QHash<QString, QSharedPointer<Figure>> figures;
    Rasterizer* rasterizer = nullptr;
    Transformer* transformer = nullptr;
    InvisibleDeleter* deleter = nullptr;
    Projecter* projecter = nullptr;

};

#endif // GRAPHICWIDGET_H
