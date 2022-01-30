#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <iostream>
#include <QAbstractSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QHash>
#include <QSlider>

class ParamBase : public QObject {
    Q_OBJECT
public:
    ParamBase(QObject* parent = nullptr);
    virtual double value() = 0;
    virtual QString name() = 0;
    virtual ~ParamBase() = default;

public slots:
    void Update();

signals:
    void Send(QString name, double value);

};


template <class T>
class Param : public ParamBase {
public:
    Param(T* _widget, ParamBase* parent = nullptr)
        : widget(_widget), ParamBase(parent) {}
    using ParamType = T;
    QString name() {
        return widget->accessibleName();
    }

    double value() {
        return double(widget->value());
    }

private:
    T* widget;
};

template<>
class Param<QCheckBox> : public ParamBase {
public:
    Param(QCheckBox* _widget)
        : widget(_widget) {}

    double value() {
        return double(widget->isChecked());
    }

    QString name() {
        return widget->accessibleName();
    }

private:
    QCheckBox* widget;
};

template<>
class Param<QComboBox> : public ParamBase {
public:
    Param(QComboBox* _widget) : widget(_widget) {}

    double value() {
        return double(widget->currentIndex());
    }

    QString name() {
        return widget->accessibleName();
    }

private:
    QComboBox* widget;
};


class ParamHandler : public QWidget
{
    Q_OBJECT
public:
    ParamHandler(QWidget* parent = 0);
    ~ParamHandler() = default;

    void Setup();

public slots:

signals:

    void SendParameter(QString param_name, double param_value);


private:

    QList<ParamBase*> param_sources;

};

#endif // PARAMHANDLER_H
