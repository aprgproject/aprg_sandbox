#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator
{

class TupcCm : public Component
{
public:
    TupcCm(ComponentName const componentName);
private:
    void handleTupcExeStartup();
    void handleTupcCmStartup();
    void handleCmBearersSetupReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersReleaseReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersModifyReqMsg(GenericMessage const& genericMessage);
    void performErqEcfMessagingToTransport();
    void performRelRlcMessagingToTransport();
    void performModMoaMessagingToTransport();
    void sendCmBearersSetupRespBasedCmBearersSetupReq(GenericMessage const& genericMessage) const;
    void sendCmBearersReleaseRespBasedCmBearersReleaseReq(GenericMessage const& genericMessage) const;
    void sendCmBearersModifyRespBasedCmBearersModifyReq(GenericMessage const& genericMessage) const;
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
};

}
