#include "graphicwidget.h"



GraphicWidget::GraphicWidget(QWidget* parent)
    : QWidget(parent) {

    pipeline.AddTransformer(&rotater);
    pipeline.AddTransformer(&light);
    pipeline.AddTransformer(&scaler);
    pipeline.AddTransformer(&projecter);
    pipeline.AddTransformer(&deleter);
    pipeline.AddTransformer(&rasterizer);

}

void GraphicWidget::SetParameter(QString param_name, double value) {
    if (!STRING_TO_PARAM.contains(param_name)) {
        throw std::logic_error("Unknown parameter: " + param_name.toStdString());
    }
    params[STRING_TO_PARAM[param_name]] = value;
    update();
}

uint qHash(const ParamName& t) {
    return qHash(static_cast<int>(t));
}

std::pair<QPolygonF, QColor> ConvertPolygon(const Polygon& polygon) {
    QPolygonF result;
    for (QVector4D v : polygon) {
        result.push_back(v.toPointF());
    }
    return {result, polygon.color};
}

QVector<std::pair<QPolygonF, QColor>> ConvertPolygons(const QVector<Polygon>& v) {
    QVector<std::pair<QPolygonF, QColor>> result;
    std::transform(v.begin(), v.end(), std::back_inserter(result), [] (const Polygon& p) {
        return ConvertPolygon(p);
    });
    return result;
}

void drawPolygons(QPainter* ptr, const QVector<std::pair<QPolygonF, QColor>>& polygons) {
    for (const auto& [polygon, color] : polygons) {
        QPen pen;
        pen.setCosmetic(true);
        pen.setWidth(1);
        pen.setColor(color);

        QPainterPath path;
        path.addPolygon(polygon);
        path.closeSubpath();
        if (color == Qt::transparent) {
            pen.setColor(Qt::black);
            ptr->setPen(pen);
            ptr->drawPath(path);
        } else {
            pen.setColor(color);
            ptr->setPen(pen);
            ptr->drawPath(path);
            ptr->fillPath(path, color);
        }


    }
}


void GraphicWidget::paintEvent(QPaintEvent* e)  {
    QPainter ptr(this);

    //std::cout << params << std::endl;

//    QPen pen;
    ptr.setRenderHint(ptr.Antialiasing);
//    pen.setCosmetic(true);
//    pen.setWidth(1);
//    ptr.setPen(pen);
    //ptr.fillRect(QRectF{QPointF{0,0}, QPointF{width(), height()}}, Qt::black);
    ptr.translate(width() / 2, height() / 2);


    ellipsoid.SetLayersCount(params[ParamName::LayerCount]);
    ellipsoid.SetPointsCount(params[ParamName::PointCount]);
    ellipsoid.SetEllipsoidCoefs(params[ParamName::A],params[ParamName::B],params[ParamName::C]);
    ellipsoid.SetTruncCoefs(params[ParamName::UpperTrunc] / 100.0, params[ParamName::LowerTrunc] / 100.0);

    scaler.SetScale(params[ParamName::Scale] / 10.0);
    rotater.SetRotation(params[ParamName::XRotation], params[ParamName::YRotation], params[ParamName::ZRotation]);

    light.SetMaterial(index_to_material[params[ParamName::Material]]);
    light.SetLightComponents(1,1,1);
    light.SetLightIntensivity({0.8,0.8,0.8});
    light.SetViewPoint({0,200,0,1});
    light.SetEnabled(params[ParamName::Light]);
    light.SetCheckPoint(rotater.TransformPoint(ellipsoid.GetInnerPoint()));

    projecter.SetEnabled(params[ParamName::Perspective]);
    projecter.SetPlaneY(750);
    projecter.SetCam({0,1400,0,1});

    deleter.SetEnabled(params[ParamName::DeleteInvisible]);
    deleter.SetViewPoint({0,1,0,0});
    deleter.SetCheckPoint({0,0,0,1});

    double radius = 60;
    double angle = M_PI * 2 * params[ParamName::LightRotation] / 360.0;
    light.SetLightSource({radius * std::cos(angle),radius * std::sin(angle),params[ParamName::LightHeight],1});


    auto polygons = ConvertPolygons(pipeline.Process(&ellipsoid));
    drawPolygons(&ptr, polygons);




}
