/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "effects/builtin/view/builtineffectmodel.h"

#include "filtercurvemodel.h"

namespace au::effects {
class FilterCurveEq;

class FilterCurveEqViewModel : public BuiltinEffectModel
{
    Q_OBJECT
    Q_PROPERTY(FilterCurveModel * curveModel READ curveModel NOTIFY curveModelChanged FINAL)
    Q_PROPERTY(double dbMin READ dbMin CONSTANT FINAL)
    Q_PROPERTY(double dbMax READ dbMax CONSTANT FINAL)

public:
    FilterCurveEqViewModel(QObject* parent, int instanceId);

    FilterCurveModel* curveModel() const;
    double dbMin() const;
    double dbMax() const;

signals:
    void curveModelChanged();

private:
    void doReload() override;

    FilterCurveModel* const m_curveModel;
};

class FilterCurveEqViewModelFactory : public EffectViewModelFactory<FilterCurveEqViewModel>
{
};
}
