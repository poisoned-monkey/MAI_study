#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <iostream>
#include <QObject>
#include <QPainter>
#include <QPolygonF>
#include <stdexcept>
#include <QWidget>
#include <QRandomGenerator>
#include <QSharedPointer>
#include <QHash>
#include <QPainterPath>
#include "graphicpipeline.h"
#include "projecter.h"
#include "coordinatetransformer.h"
#include "invisibledeleter.h"
#include "rasterizer.h"
#include "tetrahedron.h"
#include "pyramid.h"
#include "ellipsoid.h"
#include "lightprocessor.h"

//struct GraphicParameters {
//    double x_d;
//    double y_d;
//    double z_d;
//    double a;
//    double b;
//    double c;
//    double upper_trunc;
//    double lower_trunc;
//    int point_count;
//    int layer_count;
//    double scale;
//    bool perspective = false;
//    bool del_inv = false;
//    bool light = false;
//};

enum class ParamName {
    XRotation, YRotation, ZRotation, Scale,
    A,B,C,
    UpperTrunc, LowerTrunc,
    PointCount, LayerCount,
    Perspective, DeleteInvisible, Light,
    LightRotation, LightHeight,
    Material
};

uint qHash(const ParamName& t);



const QHash<QString, ParamName> STRING_TO_PARAM { // !!!!!
    {"XRotation", ParamName::XRotation},
    {"YRotation", ParamName::YRotation},
    {"ZRotation", ParamName::ZRotation},
    {"Scale", ParamName::Scale},
    {"A", ParamName::A},
    {"B", ParamName::B},
    {"C", ParamName::C},
    {"UpperTrunc", ParamName::UpperTrunc},
    {"LowerTrunc", ParamName::LowerTrunc},
    {"PointCount", ParamName::PointCount},
    {"LayerCount", ParamName::LayerCount},
    {"Perspective", ParamName::Perspective},
    {"DeleteInvisible", ParamName::DeleteInvisible},
    {"Light", ParamName::Light},
    {"LightRotation", ParamName::LightRotation},
    {"LightHeight", ParamName::LightHeight},
    {"Material", ParamName::Material}

};

const QVector<Material> index_to_material = {
    Materials::Emerald,
    Materials::Jade,
    Materials::Obsidian,
    Materials::Pearl,
    Materials::Ruby,
    Materials::Turquoise,
    Materials::Brass,
    Materials::Bronze,
    Materials::Chrome,
    Materials::Copper,
    Materials::Gold,
    Materials::Silver,
    Materials::BlackPlastic,
    Materials::CyanPlastic,
    Materials::GreenPlastic,
    Materials::RedPlastic,
    Materials::WhitePlastic,
    Materials::YellowPlastic,
    Materials::BlackRubber,
    Materials::CyanRubber,
    Materials::GreenRubber,
    Materials::RedRubber,
    Materials::WhiteRubber,
    Materials::YellowRubber
};



class GraphicWidget : public QWidget
{
    Q_OBJECT
public:
    GraphicWidget(QWidget* parent = 0);
    virtual void paintEvent(QPaintEvent* e) override;

public slots:
    void SetParameter(QString, double);



private:

    Ellipsoid ellipsoid;
    CoordinateTransformer rotater;
    CoordinateTransformer scaler;
    Projecter projecter;
    InvisibleDeleter deleter;
    Rasterizer rasterizer;
    LightProcessor light;


    GraphicPipeline pipeline;

    QHash<ParamName, double> params;
    //GraphicParameters params;

};

#endif // GRAPHICWIDGET_H
