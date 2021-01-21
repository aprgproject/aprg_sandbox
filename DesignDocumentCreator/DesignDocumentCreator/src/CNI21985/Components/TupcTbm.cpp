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
    logNoteOnComponent("TUPC/TBM saves information in TB register message.");
    log("alt if all transport bearers are ATM");
    sendTransportBearerRegisterResp();
    log("end alt");
    sendCmBearersSetupReqBasedOnTbRegisterMsg(genericMessage);
}

void TupcTbm::handleCmBearersSetupResp(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TUPC/TBM saves information in bearer setup response.");
    sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(genericMessage);
}

void TupcTbm::handleTransportConnectionSetupResp(GenericMessage const&)
{
    logNoteOnComponent("TUPC/TBM waits for all TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG. Please see Note 2");
    log("alt if not all transport bearers are ATM");
    sendTransportBearerRegisterResp();
    log("end alt");
    log("loop For all transport bearers");
    sendTransportBearerSetup();
    log("end loop");
}

void TupcTbm::handleTransportBearerUnregisterMsg(GenericMessage const& genericMessage)
{
    sendCmBearersReleaseReqBasedOnTbUnregisterMsg(genericMessage);
}

void TupcTbm::handleCmBearersReleaseResp(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TUPC/TBM saves information in bearer setup response.");
    sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(genericMessage);
}

void TupcTbm::handleTransportConnectionReleaseResp(GenericMessage const&)
{
    logNoteOnComponent("TUPC/TBM sends TC_TRANSPORT_BEARER_RELEASE_MSG for every TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG.");
    sendTransportBearerRelease();
}

void TupcTbm::handleTransportBearerModificationPrepareReqMsg(GenericMessage const& genericMessage)
{
    m_modificationTransactionType = 1;
    sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerModificationCommitReqMsg(GenericMessage const& genericMessage)
{
    m_modificationTransactionType = 2;
    sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(genericMessage);
}

void TupcTbm::handleTransportBearerModificationCancelReqMsg(GenericMessage const& genericMessage)
{
    m_modificationTransactionType = 3;
    sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(genericMessage);
}

void TupcTbm::handleCmBearersModifyResp(GenericMessage const& )
{
    if(m_modificationTransactionType==1)
    {
        sendTransportBearerModificationPrepareResp();
    }
    else if(m_modificationTransactionType==2)
    {
        sendTransportBearerModificationCommitResp();
    }
    else if(m_modificationTransactionType==3)
    {
        sendTransportBearerModificationCancelResp();
    }
}

void TupcTbm::sendCmBearersSetupReqBasedOnTbRegisterMsg(GenericMessage const& tbRegisterGenericMessage) const
{
    logNoteOnComponent("TCOM informs TUPC/TBM using CM request message at the same board (for exception please refer to Exc 1)");
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_SETUP_REQ_MSG> specificMessage;
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
    logNoteOnPreviousMessage("TUPC/TBM sends TUP_CM_BEARERS_SETUP_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportConnectionSetupReqsBasedOnCmBearersSetupResp(GenericMessage const& cmBearerGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_SETUP_RESP_MSG> cmBearerMessage(convertGenericToSpecificDynamicArray<MessageName::TUP_CM_BEARERS_SETUP_RESP_MSG>(cmBearerGenericMessage));
    SCmBearersSetupRespMsg const& cmBearerMsg(cmBearerMessage.getStaticPayloadReference());
    log("loop For all transport bearers");
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

void TupcTbm::sendTransportBearerRegisterResp() const
{
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_REGISTER_RESP_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportBearerSetup() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_SETUP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_SETUP_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersReleaseReqBasedOnTbUnregisterMsg(GenericMessage const& tbUnregisterGenericMessage) const
{
    logNoteOnComponent("TCOM informs TUPC/TBM using CM request message at the same board (for exception please refer to Exc 1)");
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_RELEASE_REQ_MSG> specificMessage;
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
    logNoteOnPreviousMessage("TUPC/TBM sends TUP_CM_BEARERS_RELEASE_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportConnectionReleaseReqsBasedOnCmBearersReleaseResp(GenericMessage const& cmBearerGenericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_RELEASE_RESP_MSG> cmBearerMessage(convertGenericToSpecificDynamicArray<MessageName::TUP_CM_BEARERS_RELEASE_RESP_MSG>(cmBearerGenericMessage));
    SCmBearersReleaseRespMsg const& cmBearerMsg(cmBearerMessage.getStaticPayloadReference());
    log("loop For all transport bearers");
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

void TupcTbm::sendTransportBearerRelease() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_RELEASE_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_RELEASE_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationPrepareReqMsg(GenericMessage const& tbModificationPrepareGenericMessage) const
{
    logNoteOnComponent("TCOM informs TUPC/TBM using CM request message at the same board (for exception please refer to Exc 1)");
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG> tbModificationPrepareMessage(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG>(tbModificationPrepareGenericMessage));
    STransportBearerModificationPrepareReq const& tbModificationPreparePayloadMsg(tbModificationPrepareMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationPreparePayloadMsg.transactionId;
    payload.cellId = tbModificationPreparePayloadMsg.cellId;
    payload.nbccId = tbModificationPreparePayloadMsg.nbccId;
    payload.numConnections = tbModificationPreparePayloadMsg.numConnections;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ETransportBearerModificationTransactionType_Prepare**");
    payload.transactionType = ETransportBearerModificationTransactionType_Prepare;
    for(unsigned int connection = 0; connection<tbModificationPreparePayloadMsg.numConnections; connection++)
    {
        SCmBearersModifyReqDynamicPart payloadDynamicPart;
        STransportBearerModificationData& tbModificationPrepareDynamicPayload(tbModificationPrepareMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payloadDynamicPart.transportBearerId = tbModificationPrepareDynamicPayload.transportBearerId;
        payloadDynamicPart.ulParameters = tbModificationPrepareDynamicPayload.ulParameters;
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationCommitReqMsg(GenericMessage const& tbModificationCommitGenericMessage) const
{
    logNoteOnComponent("TCOM informs TUPC/TBM using CM request message at the same board (for exception please refer to Exc 1)");
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG> tbModificationCommitMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG>(tbModificationCommitGenericMessage));
    STransportBearerModificationCommitReq const& tbModificationCommitPayloadMsg(tbModificationCommitMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationCommitPayloadMsg.transactionId;
    payload.cellId = tbModificationCommitPayloadMsg.cellId;
    payload.nbccId = tbModificationCommitPayloadMsg.nbccId;
    payload.numConnections = 0;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ETransportBearerModificationTransactionType_Commit**");
    payload.transactionType = ETransportBearerModificationTransactionType_Commit;
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendCmBearersModifyReqBasedOnTbModificationCancelReqMsg(GenericMessage const& tbModificationCancelGenericMessage) const
{
    logNoteOnComponent("TCOM informs TUPC/TBM using CM request message at the same board (for exception please refer to Exc 1)");
    SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARERS_MODIFY_REQ_MSG> specificMessage;
    SCmBearersModifyReqMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG> tbModificationCancelMessage(convertGenericToSpecificStatic<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_REQ_MSG>(tbModificationCancelGenericMessage));
    STransportBearerModificationCancelReq const& tbModificationCancelPayloadMsg(tbModificationCancelMessage.getStaticPayloadReference());
    payload.transactionId = tbModificationCancelPayloadMsg.transactionId;
    payload.cellId = tbModificationCancelPayloadMsg.cellId;
    payload.nbccId = tbModificationCancelPayloadMsg.nbccId;
    payload.numConnections = 0;
    logNoteOnComponent("TUPC/TBM uses transport bearer modification type as **ETransportBearerModificationTransactionType_Cancel**");
    payload.transactionType = ETransportBearerModificationTransactionType_Cancel;
    send(ComponentName::TupcCm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_REQ_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportBearerModificationPrepareResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_PREPARE_RESP_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportBearerModificationCommitResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG to TUPC/CM.");
}

void TupcTbm::sendTransportBearerModificationCancelResp() const
{
    SpecificStaticMessage<MessageName::TC_TRANSPORT_BEARER_MODIFICATION_CANCEL_RESP_MSG> specificMessage;
    //todo put the source of these parameters, demonstrate how the DB will look like
    send(ComponentName::TcomCchhRlh, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/TBM sends TC_TRANSPORT_BEARER_MODIFICATION_COMMIT_RESP_MSG to TUPC/CM.");
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
    case MessageName::TUP_CM_BEARERS_SETUP_RESP_MSG:
        handleCmBearersSetupResp(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_SETUP_RESP_MSG:
        handleTransportConnectionSetupResp(genericMessage);
        break;
    case MessageName::TC_TRANSPORT_BEARER_UNREGISTER_MSG:
        handleTransportBearerUnregisterMsg(genericMessage);
        break;
    case MessageName::TUP_CM_BEARERS_RELEASE_RESP_MSG:
        handleCmBearersReleaseResp(genericMessage);
        break;
    case MessageName::TUP_TRANSPORT_CONNECTION_RELEASE_RESP_MSG:
        handleTransportConnectionReleaseResp(genericMessage);
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
    case MessageName::TUP_CM_BEARERS_MODIFY_RESP_MSG:
        handleCmBearersModifyResp(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<endl;
    }
}

void TupcTbm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

void TupcTbm::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent "<<endl;
       break;
   }
}

}
