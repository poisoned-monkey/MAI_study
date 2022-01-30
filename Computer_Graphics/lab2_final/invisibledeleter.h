#ifndef INVISIBLEDELETER_H
#define INVISIBLEDELETER_H

#include <QObject>
#include <QVector3D>
#include <QVector4D>
#include <QWidget>
#include <QVector>

using Polygon = QVector<QVector4D>;

template <typename T>
int sign(T e) {
    return e > 0 ? 1 : (e < 0 ? -1 : 0);
}

class InvisibleDeleter : QObject
{
    Q_OBJECT
public:
    InvisibleDeleter(QObject* parent = nullptr);
    InvisibleDeleter(QVector4D _position);

    void setViewPoint(QVector4D _position);

    QVector<Polygon> deleteInvisible(QVector<Polygon>);



private:

    static QVector4D getPlaneEquation(Polygon);

    QVector4D position;
};

#endif // INVISIBLEDELETER_H
