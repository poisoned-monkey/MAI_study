#include "paramhandler.h"

ParamHandler::ParamHandler(QWidget* parent)
    : QWidget(parent) {

}

ParamHandler::~ParamHandler() {
    for (auto ptr : param_sources) {
        delete ptr;
    }
}

void ParamHandler::Setup() {
    for (auto child : children()) {
        if (QSlider* casted = qobject_cast<QSlider*>(child)) {
            param_sources.append(new Param<QSlider>(casted));
            connect(casted, static_cast<void (QAbstractSlider::*)(int)>(&QAbstractSlider::valueChanged), this, &ParamHandler::UpdateParameters);
        }
        if (QCheckBox* casted = qobject_cast<QCheckBox*>(child)) {
            param_sources.append(new Param<QCheckBox>(casted));
            connect(casted, static_cast<void (QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &ParamHandler::UpdateParameters);
        }
    }
    UpdateParameters();
}


void ParamHandler::UpdateParameters() {
    QHash<QString, double> result;
    QString prefix = "param_";
    for (auto source : param_sources) {
        result[prefix + source->name()] = source->value();
    }
    emit SendParameters(result);
}
