#pragma once

#include "ComponentName.hpp"
#include "Component.hpp"

namespace DesignDocumentCreator
{

class SampleComponent : public Component
{
public:
    SampleComponent();
    SampleComponent(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
