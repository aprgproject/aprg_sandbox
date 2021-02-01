#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class Component1 : public Component
{
public:
    Component1(ComponentName const componentName);
private:
    void handleMessage1(GenericMessage const& genericMessage);
    void handleMessageEvent(GenericMessage const& genericMessage) override;
    void handleTimerEvent(Timer const& timer) override;
    void handleOtherEvent(OtherEvent const& otherEvent) override;
};

}
