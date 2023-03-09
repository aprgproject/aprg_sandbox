#include "TupcCm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcCm::TupcCm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcCm::handleTupcExeStartup()
{
    logNoteOnComponent("TUPC/CM is **not_automatically**  started when TUPCexe starts.\nThis is same with legacy Conman.");
}

void TupcCm::handleTupcCmStartup()
{
    logNoteOnComponent("TUPC/CM is **started**.");
}

void TupcCm::handleCmBearersSetupReqMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TUPC/CM saves this information and allocates port for the connections");
    performErqEcfMessagingToTransport();
    sendCmBearersSetupRespBasedCmBearersSetupReq(genericMessage);
}

void TupcCm::handleCmBearersReleaseReqMsg(GenericMessage const& genericMessage)
{
    performRelRlcMessagingToTransport();
    sendCmBearersReleaseRespBasedCmBearersReleaseReq(genericMessage);
}

void TupcCm::handleCmBearersModifyReqMsg(GenericMessage const& genericMessage)
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> cmBearersModifyReqMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG>(genericMessage));
    SCmBearersModifyReqMsg const& cmBearersModifyReqPayload(cmBearersModifyReqMessage.getStaticPayloadReference());

    if(cmBearersModifyReqPayload.transactionType==ECmBearersModifyTransactionType_ModificationPrepare ||
            cmBearersModifyReqPayload.transactionType==ECmBearersModifyTransactionType_ModificationCommit ||
            cmBearersModifyReqPayload.transactionType==ECmBearersModifyTransactionType_ModificationCancel)
    {
        logNoteOnComponent("TUPC/CM uses legacy logic in TUPC Conman to determine if MOD is needed to be sent transport based from transactionType and change in bit rate.");
        log("alt if MOD needs to be sent");
        performModMoaMessagingToTransport();
        log("end alt");
    }
    else
    {
        performModMoaMessagingToTransport();
    }
    sendCmBearersModifyRespBasedCmBearersModifyReq(genericMessage);
}

void TupcCm::performErqEcfMessagingToTransport()
{
    logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TUPC/CM handles IPCS messaging to Transport (ERQ/ECF). \nPlease see Note 1");
}

void TupcCm::performRelRlcMessagingToTransport()
{
    logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TUPC/CM handles IPCS messaging to Transport (REL/RLC). \nPlease see Note 1");
}

void TupcCm::performModMoaMessagingToTransport()
{
    logNoteOnComponents(ComponentNames{ComponentName::TupcCm, ComponentName::Trsw}, "TUPC/CM handles IPCS messaging to Transport (MOD/MOA). \nPlease see Note 1");
}

void TupcCm::sendCmBearersSetupRespBasedCmBearersSetupReq(GenericMessage const& genericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_SETUP_RESP_MSG> specificMessage;
    SCmBearersSetupRespMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_SETUP_REQ_MSG> cmBearersSetupReqMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_SETUP_REQ_MSG>(genericMessage));
    SCmBearersSetupReqMsg const& cmBearersSetupReqPayload(cmBearersSetupReqMessage.getStaticPayloadReference());
    payload.transactionId = cmBearersSetupReqPayload.transactionId;
    payload.cellId = cmBearersSetupReqPayload.cellId;
    payload.nbccId = cmBearersSetupReqPayload.nbccId;
    payload.numConnections = cmBearersSetupReqPayload.numConnections;
    for(unsigned int connection = 0; connection<cmBearersSetupReqPayload.numConnections; connection++)
    {
        SCmBearersSetupRespDynamicPart payloadDynamicPart;
        SCmBearersSetupReqDynamicPart& cmBearersSetupReqDynamicPartPayload(cmBearersSetupReqMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        payloadDynamicPart.bearerType = cmBearersSetupReqDynamicPartPayload.bearerType;
        payloadDynamicPart.transportId = cmBearersSetupReqDynamicPartPayload.transportId;
        //payloadDynamicPart.transportBearerId = <<missing>>
        //payloadDynamicPart.btsEndPoint = <<missing>>
        //payloadDynamicPart.ftmIpta = <<missing>>
        //payloadDynamicPart.dspIpta = <<missing>>
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcTbm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/CM responds TUPC_CM_BEARERS_SETUP_RESP_MSG to TUPC/TBM.");
}

void TupcCm::sendCmBearersReleaseRespBasedCmBearersReleaseReq(GenericMessage const& genericMessage) const
{
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_RELEASE_RESP_MSG> specificMessage;
    SCmBearersReleaseRespMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_RELEASE_REQ_MSG> cmBearersReleaseReqMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_RELEASE_REQ_MSG>(genericMessage));
    SCmBearersReleaseReqMsg const& cmBearersReleaseReqPayload(cmBearersReleaseReqMessage.getStaticPayloadReference());
    payload.numConnections = cmBearersReleaseReqPayload.numConnections;
    for(unsigned int connection = 0; connection<cmBearersReleaseReqPayload.numConnections; connection++)
    {
        SCmBearersReleaseRespDynamicPart payloadDynamicPart;
        SCmBearersReleaseReqDynamicPart& cmBearersReleaseReqDynamicPartPayload(cmBearersReleaseReqMessage.getDynamicPayloadReferenceAtAndCreateIfNeeded(connection));
        //payloadDynamicPart.fpSicAddress = <<missing>>
        //payloadDynamicPart.localPort = <<missing>>
        specificMessage.addDynamicPart(payloadDynamicPart);
    }
    send(ComponentName::TupcTbm, convertSpecificDynamicArrayToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/CM responds TUPC_CM_BEARERS_RELEASE_RESP_MSG to TUPC/TBM.");
}

void TupcCm::sendCmBearersModifyRespBasedCmBearersModifyReq(GenericMessage const& genericMessage) const
{
    SpecificStaticMessage<MessageName::TUPC_CM_BEARERS_MODIFY_RESP_MSG> specificMessage;
    SCmBearersModifyRespMsg & payload(specificMessage.getStaticPayloadReference());
    SpecificDynamicArrayMessage<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG> cmBearersModifyReqMessage(convertGenericToSpecificDynamicArray<MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG>(genericMessage));
    SCmBearersModifyReqMsg const& cmBearersModifyReqPayload(cmBearersModifyReqMessage.getStaticPayloadReference());
    payload.transactionId = cmBearersModifyReqPayload.transactionId;
    payload.cellId = cmBearersModifyReqPayload.cellId;
    payload.nbccId = cmBearersModifyReqPayload.nbccId;
    //payload.response how about this
    //payload.cause how about this
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric(specificMessage));
    logNoteOnPreviousMessage("TUPC/CM responds TUPC_CM_BEARERS_MODIFY_RESP_MSG to TUPC/TBM.");
}

void TupcCm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TUPC_CM_BEARERS_SETUP_REQ_MSG:
        handleCmBearersSetupReqMsg(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_RELEASE_REQ_MSG:
        handleCmBearersReleaseReqMsg(genericMessage);
        break;
    case MessageName::TUPC_CM_BEARERS_MODIFY_REQ_MSG:
        handleCmBearersModifyReqMsg(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<"\n";
    }
}

void TupcCm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<"\n";
}

void TupcCm::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleTupcExeStartup();
       break;
   case OtherEventType::SubProcessStartup:
       handleTupcCmStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent \n";
       break;
   }
}

}
