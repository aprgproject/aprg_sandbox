#include "TupcTbm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcTbm::TupcTbm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcTbm::handleStartup()
{
    logNoteOnComponent("TUPC/TBM **automatically** starts when TUPCexe starts.");
}

void TupcTbm::handleTupcTbmConfigurationMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TUPC/TBM saves the address of TupcCm.");
    SpecificStaticMessage<MessageName::TUPC_TBM_CONFIGURATION_MSG> message(convertGenericToSpecificStatic<MessageName::TUPC_TBM_CONFIGURATION_MSG>(genericMessage));
    STupcTbmConfigurationMsg const& payload(message.getStaticPayloadReference());
    m_tupcCmAddress = payload.tupcCmSicad;
}

void TupcTbm::handleTransportBearerRegisterMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    logNoteOnComponent("TUPC/TBM saves information in TB register message.");
    log("alt if all transport bearers are ATM");
    sendTransportBearerRegisterResp();
    log("end alt");
    sendCmBearersSetupReqBasedOnTbRegisterMsg(genericMessage);
}

void TupcTbm::handleTransportBearerUnregisterMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    sendCmBearersReleaseReqBasedOnTbUnregisterMsg(genericMessage);
}

void TupcTbm::handleTransportBearerModificationPrepareReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 1;
    sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerModificationCommitReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 2;
    sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerModificationCancelReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 3;
    sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerReallocationPrepareReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 4;
    logNoteOnComponent("TUPC/TBM starts internal timer for reallocation prepare procedure. Please see Note 1.");
    sendTransportConnectionTransferReqsBasedOnReallocationPrepareReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerReallocationCommitReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 5;
    logNoteOnComponent("TUPC/TBM stops reallocation timer.");
    sendCmBearersModifyReqBasedOnReallocationCommitReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerReallocationCleanupReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 6;
    logNoteOnComponent("TUPC/TBM stops reallocation timer.");
    sendTransportConnectionReleaseReqsBasedOnReallocationCleanupReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerReallocationCancelReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TCOM informs TUPC/TBM on the same board (for exception please refer to Exc 1)");
    m_modifyTransactionType = 7;
    logNoteOnComponent("TUPC/TBM stops reallocation timer and cancels reallocation procedure");
    sendTransportBearerReallocationCancelResp();
}

void TupcTbm::handleCmBearersSetupResp(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TUPC/TBM saves information in bearer setup response.");
    sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(genericMessage);
}

void TupcTbm::handleCmBearersReleaseResp(GenericMessage const& genericMessage)
{
    sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(genericMessage);
}

void TupcTbm::handleCmBearersModifyResp(GenericMessage const& )
{
    if(m_modifyTransactionType==1)
    {
        sendTransportBearerModificationPrepareResp();
    }
    else if(m_modifyTransactionType==2)
    {
        sendTransportBearerModificationCommitResp();
    }
    else if(m_modifyTransactionType==3)
    {
        sendTransportBearerModificationCancelResp();
    }
    else if(m_modifyTransactionType==5)
    {
        sendTransportBearerReallocationPrepareResp();
    }
}

void TupcTbm::handleTransportConnectionSetupResp(GenericMessage const&)
{
    logNoteOnComponent("TUPC/TBM waits for all TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG. Please see Note 2");
    log("alt if not all transport bearers are ATM");
    sendTransportBearerRegisterResp();
    log("end alt");
    log("loop For all transport bearers in the procedure");
    sendTransportBearerSetup();
    log("end loop");
}

void TupcTbm::handleTransportConnectionReleaseResp(GenericMessage const&)
{
    if(m_modifyTransactionType==6)
    {
        logNoteOnComponent("TUPC/TBM waits for all \nTUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG.");
        sendTransportBearerReallocationCleanupResp();
    }
    else
    {
        logNoteOnComponent("TUPC/TBM sends TC_TRANSPORT_BEARER_RELEASE_MSG for every TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG.");
        sendTransportBearerRelease();
    }
}

void TupcTbm::handleTransportConnectionTransferResp(GenericMessage const&)
{
    logNoteOnComponent("TUPC/TBM waits for all TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_MSG for all the requests sent");
    sendTransportBearerReallocationPrepareResp();
}

void TupcTbm::handleCmBearersUpdateInd(GenericMessage const& genericMessage)
{
    sendTransportConnectionReleaseReqsBasedOnCmBearersUpdateInd(genericMessage);
}

void TupcTbm::sendTransportBearerRegisterResp() const
{
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_REGISTER_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerSetup() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_SETUP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_SETUP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerRelease() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_RELEASE_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_RELEASE_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerModificationPrepareResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerModificationCommitResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerModificationCancelResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerReallocationPrepareResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerReallocationCancelResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_RESP_MSG to TCOM.");
}

void TupcTbm::sendTransportBearerReallocationCleanupResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_RESP_MSG to TCOM.");
}

void TupcTbm::sendCmBearersSetupReqBasedOnTbRegisterMsg(GenericMessage const& tbRegisterGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_SETUP_REQ_MSG> specificMessage;
    SCmBearersSetupReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG> tbRegisterMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG>(tbRegisterGenericMessage));
    STransportBearerRegisterMsg const& tbRegisterPayloadMsg(tbRegisterMessage.getStaticPayloadReference());
    payload.transactionId = tbRegisterPayloadMsg.transactionId;
    payload.cellId = tbRegisterPayloadMsg.cellId;
    payload.nbccId = tbRegisterPayloadMsg.nbccId;
    payload.numConnections = tbRegisterPayloadMsg.numConnections;
    for(unsigned int connection = 0; connection<tbRegisterPayloadMsg.numConnections; connection++)
    {
        SCmBearersSetupReqDynamicPart payloadDynamicPart;
        STransportBearerLocationData& tbLocationDataPayload(tbRegisterMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payloadDynamicPart.bearerType = tbLocationDataPayload.bearerType;
        payloadDynamicPart.transportId = tbLocationDataPayload.transportId;
        payloadDynamicPart.fpLocation = tbLocationDataPayload.fpLocation;
        payloadDynamicPart.messageTypeNumber = tbLocationDataPayload.messageTypeNumber;
        payloadDynamicPart.ulParameters = tbLocationDataPayload.ulParameters;
        payloadDynamicPart.oldUlParameters = tbLocationDataPayload.oldUlParameters;
        payloadDynamicPart.rncEndPoint = tbLocationDataPayload.rncEndPoint;
        payloadDynamicPart.dsField = tbLocationDataPayload.dsField;
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_SETUP_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersReleaseReqBasedOnTbUnregisterMsg(GenericMessage const& tbUnregisterGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_RELEASE_REQ_MSG> specificMessage;
    SCmBearersReleaseReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_UNREGISTER_MSG> tbUnregisterMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_UNREGISTER_MSG>(tbUnregisterGenericMessage));
    STransportBearerUnregisterMsg const& tbUnregisterPayloadMsg(tbUnregisterMessage.getStaticPayloadReference());
    payload.transactionId = tbUnregisterPayloadMsg.transactionId;
    payload.immediateRelease = tbUnregisterPayloadMsg.immediateRelease;
    payload.skipDspConnectionRelease = tbUnregisterPayloadMsg.skipDspConnectionRelease;
    payload.unregisterType = tbUnregisterPayloadMsg.unregisterType;
    payload.cellId = tbUnregisterPayloadMsg.cellId;
    payload.nbccId = tbUnregisterPayloadMsg.nbccId;
    payload.numConnections = tbUnregisterPayloadMsg.numConnections;
    for(unsigned int connection = 0; connection<tbUnregisterPayloadMsg.numConnections; connection++)
    {
        SCmBearersReleaseReqDynamicPart payloadDynamicPart;
        TTransportBearerId& tbId(tbUnregisterMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payloadDynamicPart.transportBearerId = tbId;
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_RELEASE_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(GenericMessage const& tbModificationPrepareGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG> tbModificationPrepareMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG>(tbModificationPrepareGenericMessage));
    STransportBearerModificationPrepareReq const& tbModificationPreparePayloadMsg(tbModificationPrepareMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationPreparePayloadMsg.transactionId;
    payload.cellId = tbModificationPreparePayloadMsg.cellId;
    payload.nbccId = tbModificationPreparePayloadMsg.nbccId;
    payload.numConnections = tbModificationPreparePayloadMsg.numConnections;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ECmBearersModifyTransactionType_ModificationPrepare**");
    payload.transactionType = ECmBearersModifyTransactionType_ModificationPrepare;
    for(unsigned int connection = 0; connection<tbModificationPreparePayloadMsg.numConnections; connection++)
    {
        SCmBearersModifyReqDynamicPart payloadDynamicPart;
        STransportBearerModificationData& tbModificationPrepareDynamicPayload(tbModificationPrepareMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payloadDynamicPart.transportBearerId = tbModificationPrepareDynamicPayload.transportBearerId;
        payloadDynamicPart.ulParameters = tbModificationPrepareDynamicPayload.ulParameters;
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_MODIFY_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(GenericMessage const& tbModificationCommitGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG> tbModificationCommitMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG>(tbModificationCommitGenericMessage));
    STransportBearerModificationCommitReq const& tbModificationCommitPayloadMsg(tbModificationCommitMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationCommitPayloadMsg.transactionId;
    payload.cellId = tbModificationCommitPayloadMsg.cellId;
    payload.nbccId = tbModificationCommitPayloadMsg.nbccId;
    payload.numConnections = 0;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ECmBearersModifyTransactionType_ModificationCommit**");
    payload.transactionType = ECmBearersModifyTransactionType_ModificationCommit;
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_MODIFY_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(GenericMessage const& tbModificationCancelGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG> tbModificationCancelMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG>(tbModificationCancelGenericMessage));
    STransportBearerModificationCancelReq const& tbModificationCancelPayloadMsg(tbModificationCancelMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationCancelPayloadMsg.transactionId;
    payload.cellId = tbModificationCancelPayloadMsg.cellId;
    payload.nbccId = tbModificationCancelPayloadMsg.nbccId;
    payload.numConnections = 0;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ECmBearersModifyTransactionType_ModificationCancel**");
    payload.transactionType = ECmBearersModifyTransactionType_ModificationCancel;
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_MODIFY_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnReallocationCommitReqMsg(GenericMessage const& tbReallocationCommitGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG> tbReallocationCommitMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG>(tbReallocationCommitGenericMessage));
    STransportBearerReallocationCommitReq const& tbReallocationCommitPayloadMsg(tbReallocationCommitMessage.getStaticPayloadReference());
    payload.transactionId = tbReallocationCommitPayloadMsg.transactionId;
    payload.cellId = tbReallocationCommitPayloadMsg.cellId;
    payload.nbccId = tbReallocationCommitPayloadMsg.nbccId;
    payload.numConnections = 0;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ECmBearersModifyTransactionType_ReallocationCommit**");
    payload.transactionType = ECmBearersModifyTransactionType_ReallocationCommit;
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUPC_CM_BEARERS_MODIFY_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(GenericMessage const& cmBearerGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_SETUP_RESP_MSG> cmBearerMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_SETUP_RESP_MSG>(cmBearerGenericMessage));
    SCmBearersSetupRespMsg const& cmBearerMsg(cmBearerMessage.getStaticPayloadReference());
    log("loop For all transport bearers in the procedure");
    for(unsigned int connection = 0; connection<cmBearerMsg.numConnections; connection++)
    {
        SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG> specificMessage;
        TUP_TransportConnectionSetupReq & payload(specificMessage.getStaticPayloadReference());
        SCmBearersSetupRespDynamicPart const& dynamicPart(cmBearerMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payload.fpSicAddress = dynamicPart.fpSicAddress;
        payload.localPort = dynamicPart.localPort;
        payload.remoteAddress = dynamicPart.remoteAddress;
        payload.fpId = dynamicPart.fpId;
        send(ComponentName::Dsp, convertSpecificStaticToGeneric(specificMessage));
        logNoteOnPreviousMessage("TUPC/TBM sends TUP_TRANSPORT_CONNECTION_SETUP_REQ_MSG to DSP.");
    }
    log("end loop");
}

void TupcTbm::sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(GenericMessage const& cmBearerGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_RELEASE_RESP_MSG> cmBearerMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_RELEASE_RESP_MSG>(cmBearerGenericMessage));
    SCmBearersReleaseRespMsg const& cmBearerMsg(cmBearerMessage.getStaticPayloadReference());
    log("loop For all transport bearers in the procedure");
    for(unsigned int connection = 0; connection<cmBearerMsg.numConnections; connection++)
    {
        SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG> specificMessage;
        TUP_TransportConnectionReleaseReq & payload(specificMessage.getStaticPayloadReference());
        SCmBearersReleaseRespDynamicPart const& dynamicPart(cmBearerMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payload.fpSicAddress = dynamicPart.fpSicAddress;
        payload.localPort = dynamicPart.localPort;
        send(ComponentName::Dsp, convertSpecificStaticToGeneric(specificMessage));
        logNoteOnPreviousMessage("TUPC/TBM sends TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG to DSP.");
    }
    log("end loop");
}

void TupcTbm::sendTransportConnectionReleaseReqsBasedOnCmBearersUpdateInd(GenericMessage const& cmBearerGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_UPDATE_IND_MSG> cmBearerMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_UPDATE_IND_MSG>(cmBearerGenericMessage));
    SCmBearersUpdateIndMsg const& cmBearerMsg(cmBearerMessage.getStaticPayloadReference());
    log("loop For all transport bearers in the procedure");
    for(unsigned int connection = 0; connection<cmBearerMsg.numConnections; connection++)
    {
        SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG> specificMessage;
        TUP_TransportConnectionReleaseReq & payload(specificMessage.getStaticPayloadReference());
        SCmBearersUpdateIndDynamicPart const& dynamicPart(cmBearerMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payload.fpSicAddress = dynamicPart.fpSicAddress;
        payload.localPort = dynamicPart.localPort;
        send(ComponentName::Dsp, convertSpecificStaticToGeneric(specificMessage));
        logNoteOnPreviousMessage("TUPC/TBM sends TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG to DSP.");
    }
    log("end loop");
}

void TupcTbm::sendTransportConnectionReleaseReqsBasedOnReallocationCleanupReqMsg(GenericMessage const& tbReallocationCleanupGenericMessage) const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_MSG> tbReallocationCleanupMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_MSG>(tbReallocationCleanupGenericMessage));
    //STransportBearerReallocationCleanupReq const& tbReallocationCleanupPayload(tbReallocationCleanupMessage.getStaticPayloadReference());
    log("loop For all transport bearers in the procedure");
    //for(unsigned int connection = 0; connection<tbReallocationCleanupPayload.numConnections; connection++)
    //{
    SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG> specificMessage;
    //TUP_TransportConnectionReleaseReq & payload(specificMessage.getStaticPayloadReference());
    //The transaction should be checked here and parameters should be fetched from the transaction
    //payload.fpSicAddress = dynamicPart.fpSicAddress;
    //payload.localPort = dynamicPart.localPort;
    send(ComponentName::Dsp, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TUP_TRANSPORT_CONNECTION_RELEASE_REQ_MSG to DSP.");
    //}
    log("end loop");
}

void TupcTbm::sendTransportConnectionTransferReqsBasedOnReallocationPrepareReqMsg(GenericMessage const& tbReallocationPrepareGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_MSG> tbReallocationPrepareMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_MSG>(tbReallocationPrepareGenericMessage));
    STransportBearerReallocationPrepareReq const& tbReallocationPreparePayloadMsg(tbReallocationPrepareMessage.getStaticPayloadReference());
    log("loop For all transport bearers in the procedure");
    for(unsigned int connection = 0; connection<tbReallocationPreparePayloadMsg.numConnections; connection++)
    {
        SpecificStaticMessage<MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_MSG> specificMessage;
        //TUP_TransportConnectionTransferReq & payload(specificMessage.getStaticPayloadReference());
        //STransportBearerReallocationData const& dynamicPart(tbReallocationPrepareMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        //payload.fpSicAddress = ;
        //payload.fpId = ;
        //payload.localPort = ;
        //payload.remoteAddress = ;
        //payload.dataDuplicationAddressPresent = ;
        //payload.dataDuplicationAddress = ;
        send(ComponentName::Dsp, convertSpecificStaticToGeneric(specificMessage));
        logNoteOnPreviousMessage("TUPC/TBM sends TUP_TRANSPORT_CONNECTION_TRANSFER_REQ_MSG to DSP.");
    }
    log("end loop");
}

void TupcTbm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TUPC_TBM_CONFIGURATION_MSG:
        handleTupcTbmConfigurationMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG:
        handleTransportBearerRegisterMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_UNREGISTER_MSG:
        handleTransportBearerUnregisterMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG:
        handleTransportBearerModificationPrepareReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG:
        handleTransportBearerModificationCommitReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG:
        handleTransportBearerModificationCancelReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_REALLOCATION_PREPARE_REQ_MSG:
        handleTransportBearerReallocationPrepareReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_REALLOCATION_COMMIT_REQ_MSG:
        handleTransportBearerReallocationCommitReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CANCEL_REQ_MSG:
        handleTransportBearerReallocationCancelReqMsg(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_REALLOCATION_CLEANUP_REQ_MSG:
        handleTransportBearerReallocationCleanupReqMsg(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_SETUP_RESP_MSG:
        handleCmBearersSetupResp(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_RELEASE_RESP_MSG:
        handleCmBearersReleaseResp(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_MODIFY_RESP_MSG:
        handleCmBearersModifyResp(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_UPDATE_IND_MSG:
        handleCmBearersUpdateInd(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG:
        handleTransportConnectionSetupResp(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG:
        handleTransportConnectionReleaseResp(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_TRANSFER_RESP_MSG:
        handleTransportConnectionTransferResp(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<"\n";
    }
}

void TupcTbm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<"\n";
}

void TupcTbm::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent \n";
       break;
   }
}

}
