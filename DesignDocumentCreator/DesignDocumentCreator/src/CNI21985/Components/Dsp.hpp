#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>
#include <STCWamAddressInd.h>

namespace DesignDocumentCreator
{

class Dsp : public Component
{
public:
    Dsp(ComponentName const componentName);
    void handleTransportSetupReq(GenericMessage const& );
    void handleTransportReleaseReq(GenericMessage const& );
    void handleTransportTransferReq(GenericMessage const& );
    void sendTransportSetupResp() const;
    void sendTransportReleaseResp() const;
    void sendTransportTransferResp() const;
private:
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);};

}
