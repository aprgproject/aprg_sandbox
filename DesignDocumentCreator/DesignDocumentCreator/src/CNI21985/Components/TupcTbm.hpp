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
    void handleCmBearersSetupResp(GenericMessage const& genericMessage);
    void handleTransportConnectionSetupResp(GenericMessage const& genericMessage);
    void handleTransportBearerUnregisterMsg(GenericMessage const& genericMessage);
    void handleCmBearersReleaseResp(GenericMessage const& genericMessage);
    void handleTransportConnectionReleaseResp(GenericMessage const&);
    void handleTransportBearerModificationPrepareReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerModificationCommitReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerModificationCancelReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersModifyResp(GenericMessage const& genericMessage);
    void sendCmBearersSetupReqBasedOnTbRegisterMsg(GenericMessage const& tbRegisterGenericMessage) const;
    void sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportBearerRegisterResp() const;
    void sendTransportBearerSetup() const;
    void sendCmBearersReleaseReqBasedOnTbUnregisterMsg(GenericMessage const& tbRegisterGenericMessage) const;
    void sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportBearerRelease() const;
    void sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(GenericMessage const& tbModificationPrepareGenericMessage) const;
    void sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(GenericMessage const& tbModificationCommitGenericMessage) const;
    void sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(GenericMessage const& tbModificationCommitGenericMessage) const;
    void sendTransportBearerModificationPrepareResp() const;
    void sendTransportBearerModificationCommitResp() const;
    void sendTransportBearerModificationCancelResp() const;
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
    TAaSysComSicad m_tupcCmAddress;
    unsigned int m_modificationTransactionType;
};

}
