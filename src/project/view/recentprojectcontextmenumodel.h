/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "framework/uicomponents/qml/Muse/UiComponents/abstractmenumodel.h"

namespace au::project {
class RecentProjectContextMenuModel : public muse::uicomponents::AbstractMenuModel
{
    Q_OBJECT

public:
    RecentProjectContextMenuModel(QString path, QString displayNameOverride, QObject* parent = nullptr);

    Q_INVOKABLE void load() override;
    void handleMenuItem(const QString& itemId) override;

private:
    QString m_path;
    QString m_displayNameOverride;
};
}
