#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Components/Component.hpp>

namespace DesignDocumentCreator
{

class RF : public Component
{
public:
    RF();
    RF(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
