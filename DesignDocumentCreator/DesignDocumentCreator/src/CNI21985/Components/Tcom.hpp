#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class Tcom : public Component
{
public:
    Tcom(ComponentName const componentName);
private:
    void sendHwConfigurationResponseAck() const;
    void handleHwConfigurationMessage(GenericMessage const& genericMessage) const;

    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
};
}
