#include "paramhandler.h"

ParamHandler::ParamHandler(QWidget* parent)
    : QWidget(parent) {

}

void ParamHandler::Setup() {
    for (auto child : children()) {
        if (qobject_cast<QSpinBox*>(child)) {
            QSpinBox* casted = qobject_cast<QSpinBox*>(child);
            param_sources.append(casted);
            connect(casted, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ParamHandler::UpdateParameters);
        } else if (qobject_cast<QDoubleSpinBox*>(child)) {
            QDoubleSpinBox* casted = qobject_cast<QDoubleSpinBox*>(child);
            param_sources.append(casted);
            connect(casted, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &ParamHandler::UpdateParameters);
        }
    }
}

void ParamHandler::UpdateParameters() {
    QHash<QString, double> result;
    for (auto source : param_sources) {
         QString name = source->accessibleName();
         if (QSpinBox* ptr = qobject_cast<QSpinBox*>(source)) {
             result[name] = double(ptr->value());
         } else if (QDoubleSpinBox* ptr = qobject_cast<QDoubleSpinBox*>(source)) {
             result[name] = double(ptr->value());
         }
    }
    emit SendParameters(result);
}