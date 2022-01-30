#include "lightprocessor.h"

LightProcessor::LightProcessor(PointTransformer* parent)
    : PointTransformer(parent) {}



void LightProcessor::SetSourceColor(QColor _color) {
    source_color = {_color.red() / 255.0, _color.green() / 255.0, _color.blue() / 255.0};
}

void LightProcessor::SetViewPoint(QVector4D _point) {
    view_point = _point;
}

void LightProcessor::SetCheckPoint(QVector4D _point) {
    check_point = _point;
}


void LightProcessor::SetMaterial(Material _mat) {
    material = _mat;
}

void LightProcessor::SetLightComponents(bool _ambient, bool _diffuse, bool _specular) {
    ambient_enabled = _ambient;
    diffuse_enabled = _diffuse;
    specular_enabled = _specular;
}

Polygon LightProcessor::TransformImpl(Polygon polygon) {
    polygon.color = Qt::black;

    QVector3D normal = polygon.GetNormal(check_point).toVector3DAffine();
    QVector3D reflected = polygon.GetReflection(source, check_point);
    QVector3D to_source = source.toVector3DAffine() - polygon.Center().toVector3DAffine();
    QVector3D to_view = view_point.toVector3DAffine() - polygon.Center().toVector3DAffine();
    double distance = to_source.length();
    normal.normalize();
    reflected.normalize();
    to_source.normalize();
    to_view.normalize();

    QVector3D ambient = source_color * material.ambient;

    double diff = std::max<double>(QVector3D::dotProduct(normal, to_source), 0.);
    QVector3D diffuse = source_color * (diff * material.diffuse);

    double spec = std::pow(std::max<double>(QVector3D::dotProduct(to_view, reflected),0.), material.shininess * 100);
    QVector3D specular = source_color * (spec * material.specular);

    QVector3D result_color = (ambient * ambient_enabled) + (diffuse * diffuse_enabled) + (specular * specular_enabled);
    result_color *= 255.0;

    polygon.color = QColor{result_color.x(), result_color.y(), result_color.z()};
    return polygon;
}

void LightProcessor::SetLightSource(QVector4D _source) {
    source = _source;
}

void LightProcessor::SetLightIntensivity(QVector3D _intensivity) {
    source_color = _intensivity;
}

QVector<Polygon> LightProcessor::TransformImpl(QVector<Polygon> polygons) {
    for (Polygon& polygon : polygons) {
        polygon = TransformImpl(std::move(polygon));
    }
    return polygons;
}

