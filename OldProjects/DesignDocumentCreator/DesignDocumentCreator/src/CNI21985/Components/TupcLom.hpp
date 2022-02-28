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
    void handleHwConfigurationMessage(GenericMessage const& genericMessage);
    void saveAddresses(GenericMessage const& genericMessage);
    void handleTcomDeploymentMessage(GenericMessage const& genericMessage);
    void sendTupcTbmConfigurationMsg(TAaSysComSicad const ) const;
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
    TAaSysComSicad m_oamAddress;
    TAaSysComSicad m_tupcCmAddress;
    TAaSysComSicad m_tupcIlmAddress;
};

}
