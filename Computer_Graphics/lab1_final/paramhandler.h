#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QAbstractSpinBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QHash>


class ParamHandler : public QWidget
{
    Q_OBJECT
public:
    ParamHandler(QWidget* parent = 0);

    void Setup();

public slots:

    void UpdateParameters();

signals:

    void SendParameters(QHash<QString, double> in_params);

private:

    QList<QAbstractSpinBox*> param_sources;

};

#endif // PARAMHANDLER_H