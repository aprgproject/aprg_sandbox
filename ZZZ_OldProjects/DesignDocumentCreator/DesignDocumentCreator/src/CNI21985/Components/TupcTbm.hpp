#pragma once

#include <Common/Components/Component.hpp>
#include <Common/Components/ComponentName.hpp>

namespace DesignDocumentCreator {

class TupcTbm : public Component {
public:
    TupcTbm(ComponentName const componentName);

private:
    void handleStartup();
    void handleTupcTbmConfigurationMsg(GenericMessage const& genericMessage);
    void handleTransportBearerRegisterMsg(GenericMessage const& genericMessage);
    void handleTransportBearerUnregisterMsg(GenericMessage const& genericMessage);
    void handleTransportBearerModificationPrepareReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerModificationCommitReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerModificationCancelReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerReallocationPrepareReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerReallocationCommitReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerReallocationCancelReqMsg(GenericMessage const& genericMessage);
    void handleTransportBearerReallocationCleanupReqMsg(GenericMessage const& genericMessage);
    void handleCmBearersSetupResp(GenericMessage const& genericMessage);
    void handleCmBearersReleaseResp(GenericMessage const& genericMessage);
    void handleCmBearersModifyResp(GenericMessage const& genericMessage);
    void handleTransportConnectionSetupResp(GenericMessage const& genericMessage);
    void handleTransportConnectionReleaseResp(GenericMessage const&);
    void handleTransportConnectionTransferResp(GenericMessage const&);
    void handleCmBearersUpdateInd(GenericMessage const& genericMessage);
    void sendTransportBearerRegisterResp() const;
    void sendTransportBearerSetup() const;
    void sendTransportBearerRelease() const;
    void sendTransportBearerModificationPrepareResp() const;
    void sendTransportBearerModificationCommitResp() const;
    void sendTransportBearerModificationCancelResp() const;
    void sendTransportBearerReallocationPrepareResp() const;
    void sendTransportBearerReallocationCancelResp() const;
    void sendTransportBearerReallocationCleanupResp() const;
    void sendCmBearersSetupReqBasedOnTbRegisterMsg(GenericMessage const& tbRegisterGenericMessage) const;
    void sendCmBearersReleaseReqBasedOnTbUnregisterMsg(GenericMessage const& tbRegisterGenericMessage) const;
    void sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(
        GenericMessage const& tbModificationPrepareGenericMessage) const;
    void sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(
        GenericMessage const& tbModificationCommitGenericMessage) const;
    void sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(
        GenericMessage const& tbModificationCancelGenericMessage) const;
    void sendCmBearersModifyReqBasedOnReallocationCommitReqMsg(
        GenericMessage const& tbReallocationCommitGenericMessage) const;
    void sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(
        GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportConnectionReleaseReqsBasedOnCmBearersUpdateInd(
        GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportConnectionReleaseReqsBasedOnReallocationCleanupReqMsg(
        GenericMessage const& cmBearerGenericMessage) const;
    void sendTransportConnectionTransferReqsBasedOnReallocationPrepareReqMsg(
        GenericMessage const& tbReallocationPrepareGenericMessage) const;
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    virtual void handleOtherEvent(OtherEvent const& otherEvent);
    TAaSysComSicad m_tupcCmAddress;
    unsigned int m_modifyTransactionType;
};

}  // namespace DesignDocumentCreator
