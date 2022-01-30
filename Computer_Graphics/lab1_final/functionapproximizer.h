#ifndef FUNCTIONAPPROXIMIZER_H
#define FUNCTIONAPPROXIMIZER_H

#include<QVector>
#include<QPoint>
#include<QPair>
#include<tuple>
#include<cmath>

#include<algorithm>

class FunctionApproximizer
{
public:
    FunctionApproximizer() = default;

    const QVector<QPointF>& GetPoints(int n, double a, double B) const;


private:

    double ApproximatedFunc(double x, double a, double B) const;

    mutable QPair<bool, QVector<QPointF>> cache = {false, {}};
    mutable std::tuple<int, double, double> cached_params;
    
};

#endif // FUNCTIONAPPROXIMIZER_H