/*
* Audacity: A Digital Audio Editor
*/

#pragma once

#include <chrono>

#include "au3-basic-ui/BasicUI.h" // For ProgressResult

#include "framework/global/modularity/ioc.h"
#include "framework/global/async/asyncable.h"
#include "framework/interactive/iinteractive.h"

using ProgressResult = BasicUI::ProgressResult;

namespace au::au3 {
class ProgressDialog : public BasicUI::ProgressDialog, public muse::async::Asyncable, public muse::Contextable
{
    muse::ContextInject<muse::IInteractive> interactive { this };

public:
    ProgressDialog(const muse::modularity::ContextPtr& ctx, const TranslatableString& title = {});
    ProgressDialog(const muse::modularity::ContextPtr& ctx, const std::string& title);

public:
    virtual ~ProgressDialog();

    void Reinit() override;

    void SetDialogTitle(const TranslatableString& title) override;

public:
    ProgressResult Poll(
        unsigned long long numerator, unsigned long long denominator, const TranslatableString& message = {}) override;

    void SetMessage(const TranslatableString& message) override;

    bool cancelled() const
    {
        return m_cancelled;
    }

    //! Underlying progress channel. NOTE: calling this implicitly opens
    //! the QML dialog if it hasn't been shown yet — callers that publish
    //! through `muse::Progress` directly (e.g. plugin scanners that drive
    //! `muse::Progress::progress(...)` instead of `Poll()`) would
    //! otherwise miss the lazy mount inside `Poll()` and the dialog
    //! would never appear.
    muse::Progress& museProgress();

private:
    void ensureShown();

    mutable muse::Progress m_progress;
    std::string m_progressTitle;
    std::string m_progressMessage;
    bool m_cancelled = false;
    bool m_canceledHooked = false;
    std::chrono::steady_clock::time_point m_lastEventPump {};
};
}
