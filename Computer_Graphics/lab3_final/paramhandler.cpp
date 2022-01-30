#include "paramhandler.h"

ParamHandler::ParamHandler(QWidget* parent)
    : QWidget(parent) {

}

ParamBase::ParamBase(QObject* parent)
    : QObject(parent) {}



void ParamBase::Update() {
    emit Send(name(), value());
}

void ParamHandler::Setup() {
    for (auto child : children()) {
        bool new_element = false;
        if (QSlider* casted = qobject_cast<QSlider*>(child)) {
            param_sources.append(new Param<QSlider>(casted));
            connect(casted, static_cast<void (QAbstractSlider::*)(int)>(&QAbstractSlider::valueChanged), param_sources.back(), &ParamBase::Update);
            new_element = true;
        }
        if (QCheckBox* casted = qobject_cast<QCheckBox*>(child)) {
            param_sources.append(new Param<QCheckBox>(casted));
            connect(casted, static_cast<void (QCheckBox::*)(int)>(&QCheckBox::stateChanged), param_sources.back(), &ParamBase::Update);
            new_element = true;
        }
        if (QSpinBox* casted = qobject_cast<QSpinBox*>(child)) {
            param_sources.append(new Param<QSpinBox>(casted));
            connect(casted, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), param_sources.back(), &ParamBase::Update);
            new_element = true;
        }
        if (QComboBox* casted = qobject_cast<QComboBox*>(child)) {
            param_sources.append(new Param<QComboBox>(casted));
            connect(casted, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), param_sources.back(), &ParamBase::Update);
            new_element = true;
        }
        if (new_element) {
            connect(param_sources.back(), &ParamBase::Send, this, &ParamHandler::SendParameter);
        }
    }
    for (ParamBase* ptr : param_sources) {
        ptr->setParent(this);
        ptr->Update();
    }
}


//void ParamHandler::UpdateParameter(QString name, double value) {
//    emit SendParameters(name, value);
//}
