/*
* Audacity: A Digital Audio Editor
*/
#include "cloudprojectcontextmenumodel.h"

#include "framework/actions/actiontypes.h"

using namespace au::project;

namespace {
constexpr const char* OPEN_PROJECT_PAGE_ACTION = "audacity://cloud/open-project-page";
}

CloudProjectContextMenuModel::CloudProjectContextMenuModel(QString projectId, QString slug, QObject* parent)
    : AbstractMenuModel(parent), m_projectId(std::move(projectId)), m_slug(std::move(slug))
{
}

void CloudProjectContextMenuModel::load()
{
    muse::uicomponents::AbstractMenuModel::load();

    muse::uicomponents::MenuItem* viewProjectPage = makeMenuItem(OPEN_PROJECT_PAGE_ACTION);

    setItems({ viewProjectPage });
}

void CloudProjectContextMenuModel::handleMenuItem(const QString& itemId)
{
    if (itemId == OPEN_PROJECT_PAGE_ACTION) {
        if (m_projectId.isEmpty()) {
            return;
        }

        muse::actions::ActionQuery query(OPEN_PROJECT_PAGE_ACTION);
        query.addParam("slug", muse::Val(m_projectId));
        dispatch(query);
        return;
    }

    AbstractMenuModel::handleMenuItem(itemId);
}
