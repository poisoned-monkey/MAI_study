#ifndef PROJECTER_H
#define PROJECTER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QVector4D>
#include <QVector3D>

class Projecter : public QObject
{
    Q_OBJECT
public:
    Projecter(QObject* parent = nullptr);

    QVector<QVector4D> project(const QVector<QVector4D>& to_project);

    Projecter& setPlaneY(double _y);
    Projecter& setCam(QVector4D _cam);

signals:
    void updated();

private:
    double y = 0;
    QVector4D cam;


};

#endif // PROJECTER_H
