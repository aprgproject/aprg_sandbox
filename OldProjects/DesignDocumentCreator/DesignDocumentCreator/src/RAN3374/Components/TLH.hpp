#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TLH : public Component
{
public:
    TLH();
    TLH(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
