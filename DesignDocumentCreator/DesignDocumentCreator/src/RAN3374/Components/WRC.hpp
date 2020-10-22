#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Components/Component.hpp>

namespace DesignDocumentCreator
{

class WRC : public Component
{
public:
    WRC();
    WRC(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
