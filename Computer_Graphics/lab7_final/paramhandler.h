#ifndef PARAMHANDLER_H
#define PARAMHANDLER_H

#include <QWidget>
#include <QVector>
#include <QDoubleSpinBox>

class ParamHandler : public QWidget
{
    Q_OBJECT
public:
    explicit ParamHandler(QWidget *parent = nullptr);

    void Setup();

public slots:
    void UpdateParams();

signals:

    void Send(QVector<double>);

private:
    QVector<QDoubleSpinBox*> boxes;
};

#endif // PARAMHANDLER_H
