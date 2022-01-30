#ifndef NURBESTIMATOR_H
#define NURBESTIMATOR_H

#include <QObject>
#include <QPainterPath>
#include <QWidget>
#include <iostream>
#include <QVector>
#include <QMap>
#include <optional>
#include <tuple>


class NURBEstimator : QObject
{
    Q_OBJECT
public:
    NURBEstimator() = default;
    NURBEstimator(QVector<QPointF> _points, int k, double weight);

    void SetPartPointCount(int _count);

    QVector<QPainterPath> UpdateNthPoint(int index, QPointF position);
    QVector<QPainterPath> GetAll();
    void SetWeights(QVector<double> _weights);

private:

    QPointF CalculatePoint(double t);
    double DeBoor(double t, int i, int k);

    QMap<std::tuple<double, int, int>, double> boor_cache;
    QVector<double> t_coefs;
    QVector<double> weights;
    QVector<QPointF> points;
    const int k = 0;
    const int n = 0;
    int part_point_count = 100;
};

#endif // NURBESTIMATOR_H
