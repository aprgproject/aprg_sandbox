#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

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


