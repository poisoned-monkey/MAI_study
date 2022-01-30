#include "graphicwidget.h"




GraphicWidget::GraphicWidget(QWidget* parent)
    : QWidget(parent) {
    transformer = new Transformer(this);
    rasterizer = new Rasterizer(this);
    deleter = new InvisibleDeleter(this);
    projecter = new Projecter(this);


    projecter->setPlaneY(150);
    projecter->setCam({0,-500,0,1});

    QVector4D view_vector = {0,1,0,0};
    deleter->setViewPoint(view_vector);


    //figures["Cube"] = QSharedPointer<Square>::create(10);
    figures["Pyramid"] = QSharedPointer<Pyramid>::create();

    for (auto& fig : figures) {
        fig->setRasterizer(rasterizer)
            .setTransformer(transformer)
            .setInvisibleDeleter(deleter)
            .setProjecter(projecter);
    }

}

std::ostream& operator << (std::ostream& os, const GraphicParameters& params) {
    os << "upper_radius " << params.u_r << "\n"
       << "lower_radius " << params.l_r << "\n"
       << "height " << params.height << "\n"
       << "x_d " << params.x_d << "\n"
       << "y_d " << params.y_d << "\n"
       << "z_d " << params.z_d << "\n"
       << "scale " << params.scale << "\n";

    return os;
}

void GraphicWidget::SetParameters(QHash<QString, double> in_params) {
    QString param_prefix = "param_";
    params.x_d = in_params[param_prefix + "x_d"];
    params.y_d = in_params[param_prefix + "y_d"];
    params.z_d = in_params[param_prefix + "z_d"];
    params.u_r = in_params[param_prefix + "u_r"];
    params.l_r = in_params[param_prefix + "l_r"];
    params.height = in_params[param_prefix + "height"];
    params.scale = in_params[param_prefix + "scale"];
    params.perspective = in_params[param_prefix + "perspective"];
    params.del_inv = in_params[param_prefix + "del_inv"];
    update();
}


void GraphicWidget::paintEvent(QPaintEvent* e) {
    QPainter ptr(this);

    //std::cout << params << std::endl;

    QPen pen;
    pen.setCosmetic(true);
    pen.setWidth(2);
    ptr.setPen(pen);
    ptr.translate(width() / 2, height() / 2);
    ptr.setRenderHint(QPainter::Antialiasing);

    qobject_cast<Pyramid*>(figures["Pyramid"].get())->changeParameters(params.height, params.l_r, params.u_r);
    transformer->setScale(params.scale / 10.0)
                .setRotation(params.x_d, params.y_d, params.z_d);

    figures["Pyramid"]->setProjecter(params.perspective ? projecter : nullptr);
    figures["Pyramid"]->setInvisibleDeleter(params.del_inv ? deleter : nullptr);

    //figures["Cube"]->paint(&ptr);
    figures["Pyramid"]->paint(&ptr);



}
