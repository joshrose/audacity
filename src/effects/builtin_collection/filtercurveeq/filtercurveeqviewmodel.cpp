/*
 * Audacity: A Digital Audio Editor
 */
#include "filtercurveeqviewmodel.h"

#include "filtercurveeq.h"
#include "filtercurvemodel.h"

namespace au::effects {
FilterCurveEqViewModel::FilterCurveEqViewModel(QObject* parent, int instanceId)
    : BuiltinEffectModel{parent, instanceId},
    m_curveModel(new FilterCurveModel(this, effect<FilterCurveEq>()))
{
}

void FilterCurveEqViewModel::doReload()
{
    m_curveModel->reload();
    emit curveModelChanged();
}

FilterCurveModel* FilterCurveEqViewModel::curveModel() const
{
    return m_curveModel;
}

double FilterCurveEqViewModel::dbMin() const
{
    return -30.0;
}

double FilterCurveEqViewModel::dbMax() const
{
    return 30.0;
}
}
