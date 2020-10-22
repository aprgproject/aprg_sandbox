#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Components/Component.hpp>

namespace DesignDocumentCreator
{
class SampleComponent : public Component
{
public:    SampleComponent();
    SampleComponent(ComponentName const componentName);
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    ComponentName m_componentName;
};

}
