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

class ProgressDialog : public BasicUI::ProgressDialog, public muse::async::Asyncable, public muse::Contextable
{
    muse::ContextInject<muse::IInteractive> m_injectedInteractive { this };
    muse::IInteractive* m_explicitInteractive { nullptr };

    muse::IInteractive* interactive() const;

public:
    ProgressDialog(const muse::modularity::ContextPtr& ctx, const TranslatableString& title = {});
    ProgressDialog(const muse::modularity::ContextPtr& ctx, const std::string& title);

    //! Construct with an already-resolved IInteractive. Bypasses ContextInject so
    //! callers that don't sit inside a per-window IoC context (e.g. host code
    //! injected via GlobalInject) can still use the dialog without tripping
    //! muse's ioc assertion.
    ProgressDialog(muse::IInteractive& interactive, const TranslatableString& title = {});
    ProgressDialog(muse::IInteractive& interactive, const std::string& title);

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

    void start();
    muse::Progress& progress() { return m_progress; }

private:
    mutable muse::Progress m_progress;
    std::string m_progressTitle;
    std::string m_progressMessage;
    bool m_cancelled = false;
    bool m_canceledHooked = false;
    std::chrono::steady_clock::time_point m_lastEventPump {};
};
