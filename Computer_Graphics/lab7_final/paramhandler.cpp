#include "paramhandler.h"

ParamHandler::ParamHandler(QWidget *parent) : QWidget(parent)
{

}



void ParamHandler::Setup() {
    for (QObject* child : children()) {
        if (QDoubleSpinBox* casted = qobject_cast<QDoubleSpinBox*>(child))  {
            boxes.append(casted);
            connect(casted, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &ParamHandler::UpdateParams);
        }
    }
    UpdateParams();
}

void ParamHandler::UpdateParams() {
    QVector<double> to_send(boxes.size());
    for (QDoubleSpinBox* box : boxes) {
        to_send[box->accessibleName().toInt()] = box->value();
    }
    emit Send(to_send);
}
