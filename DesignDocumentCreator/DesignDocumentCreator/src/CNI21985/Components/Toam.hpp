#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator
{

class TcomToam : public Component
{
    class HwConfiguration
    {    public:
        //this is fake
        void saveConfiguration(SHwConfigurationMsg const& hwConfigurationMsg);
        STCWamAddressIndNew generateWamAddressInd() const;
    };
public:
    TcomToam(ComponentName const componentName);
private:
    void handleHwConfigurationMessage(GenericMessage const& genericMessage);
    void handleLinkStatesMessage(GenericMessage const& genericMessage) const;    void sendHwConfigurationResponseAck() const;
    void sendsLinkStatesResponse() const;
    void sendsTcomDeploymentInd() const;
    void saveConfiguration(SHwConfigurationMsg const& hwConfigurationMsg);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    HwConfiguration m_configuration;
};

}
