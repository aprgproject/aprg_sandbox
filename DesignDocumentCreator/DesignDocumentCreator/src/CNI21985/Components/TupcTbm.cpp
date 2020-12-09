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
    logNoteOnComponent("TupcTbm **automatically** starts when TUPCexe starts.");
}

void TupcTbm::handleTupcTbmConfigurationMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TupcTbm saves the address of TupcCm.");
    SpecificStaticMessage<MessageName::TUPC_TBM_CONFIGURATION_MSG> message(convertGenericToSpecificStatic<MessageName::TUPC_TBM_CONFIGURATION_MSG>(genericMessage));
    STupcTbmConfigurationMsg const& payload(message.getPayloadReference());
    m_tupcCmAddress = payload.tupcCmSicad;
}

void TupcTbm::handleTransportBearerRegisterMsg(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TupcTbm saves the address of TupcCm.");
    SpecificDynamicArrayMessage<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, 20> message(convertGenericToSpecificDynamicArray<MessageName::TC_TRANSPORT_BEARER_REGISTER_MSG, 20>(genericMessage));
    STransportBearerRegisterMsg const& payload(message.getStaticPayloadReference());
}

void TupcTbm::sendCmBearerSetupReqBasedOnTbRegisterMsg(STransportBearerRegisterMsg const& tbRegisterMsg) const
{
    /*SpecificDynamicArrayMessage<MessageName::TUP_CM_BEARER_SETUP_REQ_MSG, 20> specificMessage;
    SCmBearerSetupReqMsg & payload(specificMessage.getStaticPayloadReference());
    payload.transactionId = tbRegisterMsg.transactionId;
    payload.cellId = tbRegisterMsg.cellId;
    payload.nbccId = tbRegisterMsg.nbccId;
    payload.numConnections = tbRegisterMsg.numConnections;
    for(unsigned int )
    send(ComponentName::Oam, convertSpecificStaticToGeneric<MessageName::TC_HW_CONFIGURATION_RESP_MSG>(specificMessage));
    logNoteOnPreviousMessage("TCOM/TOAM sends HW configuration ack to OAM.");*/
}

void TupcTbm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TUPC_TBM_CONFIGURATION_MSG:
        handleTupcTbmConfigurationMsg(genericMessage);
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
