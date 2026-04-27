/*
 * Audacity: A Digital Audio Editor
 */
#include "filtercurvemodel.h"

#include "filtercurveeq.h"

#include "au3-builtin-effects/EqualizationCurvesList.h"
#include "au3-builtin-effects/EqualizationFilter.h"
#include "au3-mixer/Envelope.h"

namespace au::effects {
FilterCurveModel::FilterCurveModel(QObject* parent, FilterCurveEq& eq)
    : QObject(parent), m_eq(eq)
{
}

void FilterCurveModel::reload()
{
    auto& parameters = m_eq.mCurvesList.mParameters;
    parameters.mDrawMode = true;

    rebuildPoints();
    emit pointsChanged();
}

QVector<QPointF> FilterCurveModel::points() const
{
    return m_points;
}

double FilterCurveModel::defaultValue() const
{
    return 0.0;
}

void FilterCurveModel::rebuildPoints()
{
    m_points.clear();

    const auto& env = m_eq.mCurvesList.mParameters.mLogEnvelope;
    const size_t n = env.GetNumberOfPoints();
    if (n == 0) {
        return;
    }

    std::vector<double> when(n);
    std::vector<double> value(n);
    env.GetPoints(when.data(), value.data(), static_cast<int>(n));

    m_points.reserve(static_cast<int>(n));
    for (size_t i = 0; i < n; ++i) {
        m_points.append(QPointF(when[i], value[i]));
    }
}
}
