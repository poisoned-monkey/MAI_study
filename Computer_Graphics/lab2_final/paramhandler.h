#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QAbstractSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QHash>
#include <QSlider>

class ParamBase {
public:
    virtual double value() = 0;
    virtual QString name() = 0;
    virtual ~ParamBase() = default;
};

template <class T>
class Param : public ParamBase {
public:
    Param(T* _widget)
        : widget(_widget) {}

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


class ParamHandler : public QWidget
{
    Q_OBJECT
public:
    ParamHandler(QWidget* parent = 0);
    ~ParamHandler();

    void Setup();

public slots:

    void UpdateParameters();

signals:

    void SendParameters(QHash<QString, double> in_params);


private:

    QList<ParamBase*> param_sources;

};

#endif // PARAMHANDLER_H
