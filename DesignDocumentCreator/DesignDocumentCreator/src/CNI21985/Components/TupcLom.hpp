#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcLom : public Component
{
public:
    TupcLom(ComponentName const componentName);
private:
    void handleStartup();
    void handleHwConfiguration(GenericMessage const& genericMessage);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
    TAaSysComSicad m_oamAddress;
};
}