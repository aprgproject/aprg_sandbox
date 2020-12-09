#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcTbm : public Component
{
public:
    TupcTbm(ComponentName const componentName);
private:
    void handleStartup();
    void handleTupcTbmConfigurationMsg(GenericMessage const& genericMessage);
    void handleTransportBearerRegisterMsg(GenericMessage const& genericMessage);
    void sendCmBearerSetupReqBasedOnTbRegisterMsg(STransportBearerRegisterMsg const& tbRegisterMsg) const;
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
    TAaSysComSicad m_tupcCmAddress;
};

}
