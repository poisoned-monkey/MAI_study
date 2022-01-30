#include "nurbestimator.h"


NURBEstimator::NURBEstimator(QVector<QPointF> _points, int _k, double weight)
    : points(std::move(_points)), k(_k), n(points.size() - 1) {
    t_coefs.resize(n + k + 1);
    weights = QVector<double>(points.size(), weight);
    double cur = 0;
    //double step = 1 / double(n + k);
    for (double& i : t_coefs) {
        i = cur;
        cur++;
        //cur += step;
    }
}

//QVector<QVector<QPointF>> NURBEstimator::GetAllParts() {

//}

QVector<QPainterPath> NURBEstimator::UpdateNthPoint(int index, QPointF position) {
    points[index] = position;
    QVector<QPainterPath> result;
    for (int i = index; i < index + k; ++i) {
        QPainterPath curve_part(CalculatePoint(i));
        for (int j = 1; j <= part_point_count; ++j) {
            curve_part.lineTo(CalculatePoint(i + (j / double(part_point_count))));
        }
        result.push_back(curve_part);
    }
    return result;
}

QVector<QPainterPath> NURBEstimator::GetAll() {

    QVector<QPainterPath> result;
    for (int i = 0; i < (int)t_coefs.back(); ++i) {
        QPainterPath curve_part(CalculatePoint(i));
        for (int j = 1; j <= part_point_count; ++j) {
            curve_part.lineTo(CalculatePoint(i + (j / double(part_point_count))));
        }
        result.push_back(curve_part);
    }
    return result;
}

QPointF NURBEstimator::CalculatePoint(double t) {
    QPointF result;
    double de_boor_sum = 0;
    double weight_sum = 0;
    for (int i = 0; i < n + 1; ++i) {
        double de_boor_coef = DeBoor(t,i + 1,k);
        result += points[i] * de_boor_coef * weights[i];
        weight_sum += weights[i] * de_boor_coef;
        de_boor_sum += de_boor_coef;
    }

    //std::cout << sum << std::endl;
    if (de_boor_sum < 1) {
        result += (1 - de_boor_sum) * ((t < (n + k) / 2.) ? points[0] * weights[0] : points.back() * weights.back());
        weight_sum += (1 - de_boor_sum) * ((t < (n + k) / 2.) ? weights[0] : weights.back());
    }
    return result / weight_sum;
}

void NURBEstimator::SetPartPointCount(int _count) {
    part_point_count = _count;
    boor_cache.clear();
}

void NURBEstimator::SetWeights(QVector<double> _weights) {
    weights = _weights;
    boor_cache.clear();
}

double NURBEstimator::DeBoor(double t, int i, int k) {

    //осторожно с i
    --i;
    if (boor_cache.contains({t,i,k})) {
        return boor_cache[std::tuple<double,int,int>{t,i,k}];
    }
    if (k == 1) {
        return (t >= t_coefs[i] && t < t_coefs[i + 1]) ? 1 : 0;
    }
    double first_part = 0, second_part = 0;
    if (t_coefs[i + k - 1] != t_coefs[i]) {
        first_part = ((t - t_coefs[i]) * DeBoor(t, i + 1, k - 1))
                                    /
                     (t_coefs[i + k - 1] - t_coefs[i]);
    }
    if (t_coefs[i + k] != t_coefs[i + 1]) {
        second_part = ((t_coefs[i + k] - t) * DeBoor(t, i + 2, k - 1))
                                    /
                         (t_coefs[i + k] - t_coefs[i + 1]);
    }
    boor_cache[std::tuple<double,int,int>{t,i,k}] = first_part + second_part;
    return first_part + second_part;
}
