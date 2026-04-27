/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include <QObject>
#include <QPointF>
#include <QVector>

namespace au::effects {
class FilterCurveEq;

class FilterCurveModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> points READ points NOTIFY pointsChanged FINAL)
    Q_PROPERTY(double defaultValue READ defaultValue CONSTANT FINAL)

public:
    FilterCurveModel(QObject* parent, FilterCurveEq& eq);

    void reload();

    QVector<QPointF> points() const;
    double defaultValue() const;

signals:
    void pointsChanged();

private:
    void rebuildPoints();

    FilterCurveEq& m_eq;
    QVector<QPointF> m_points;
};
}
