/*
* Audacity: A Digital Audio Editor
*/
#include "recentprojectcontextmenumodel.h"

#include "framework/actions/actiontypes.h"

#include <QUrl>

using namespace au::project;

namespace {
constexpr const char* OPEN_PROJECT_ACTION = "file-open";
}

RecentProjectContextMenuModel::RecentProjectContextMenuModel(QString path, QString displayNameOverride, QObject* parent)
    : AbstractMenuModel(parent), m_path(std::move(path)), m_displayNameOverride(std::move(displayNameOverride))
{
}

void RecentProjectContextMenuModel::load()
{
    muse::uicomponents::AbstractMenuModel::load();

    muse::uicomponents::MenuItem* openItem = makeMenuItem(OPEN_PROJECT_ACTION);

    setItems({ openItem });
}

void RecentProjectContextMenuModel::handleMenuItem(const QString& itemId)
{
    if (itemId == OPEN_PROJECT_ACTION) {
        dispatcher()->dispatch("file-open",
                               muse::actions::ActionData::make_arg2<QUrl, QString>(
                                   QUrl::fromLocalFile(m_path), m_displayNameOverride));
        return;
    }

    AbstractMenuModel::handleMenuItem(itemId);
}
