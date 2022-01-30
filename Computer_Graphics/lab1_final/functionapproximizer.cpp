#include "functionapproximizer.h"



double FunctionApproximizer::ApproximatedFunc(double x, double a, double B) const {
    return std::sqrt(std::pow(x, 3) / (a - x));
}


const QVector<QPointF>& FunctionApproximizer::GetPoints(int n, double a, double B) const {
    int cached_n;
    double cached_a,cached_B;
    std::tie(cached_n, cached_a, cached_B) = cached_params;

    if (cache.first && cached_n == n && cached_a == a && cached_B == B) {
        return cache.second;
    }

    QVector<QPointF> first;
    double step = std::min(a,B) / double(n);
    for (int i = 0; i < n; ++i) {
        double x = i * step;
        if (a - x == 0) {
            x -= 0.01;
        }
        first.push_back(QPointF(x, ApproximatedFunc(x, a, B)));
    }
    QVector<QPointF> second = first;
    std::reverse(second.begin(), second.end());
    second.pop_back();
    std::for_each(second.begin(), second.end(), [] (QPointF& point) {
        point.setY(-point.y());
    });
    second << first;

    cached_params = std::make_tuple(n,a,B);
    cache.second = second;
    cache.first = true;
    return cache.second;
}