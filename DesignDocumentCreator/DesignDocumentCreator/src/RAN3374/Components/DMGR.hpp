#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class DMGR : public Component
{
public:
    DMGR();
    DMGR(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}


