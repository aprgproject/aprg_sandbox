#include "TupcLom.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <utils/AddressHelper.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcLom::TupcLom(ComponentName const componentName)
    : Component(componentName)
{}

void TupcLom::handleStartup()
{
    logNoteOnComponent("TupcLom **automatically**  starts when TUPCexe starts.\nThis is same with legacy.");
}

void TupcLom::handleHwConfigurationMessage(GenericMessage const& genericMessage)
{
    Environment & environment(Environment::getInstance());
    logNoteOnPreviousMessage("OAM sends this message to only one TUPC instance.\nThe receiver will be the location of TupcCm.");
    logNoteOnComponent("TupcLom saves hardware configuration.");
    saveAddresses(genericMessage);
    logNoteOnComponents(ComponentNames{ComponentName::TupcLom, ComponentName::TupcCm}, "TupcLom starts TupcCm on the same location.");
    environment.getComponentPointer(ComponentName::TupcCm)->pushBackEvent(Event(OtherEvent(OtherEventType::SubProcessStartup)));
}

void TupcLom::saveAddresses(GenericMessage const& genericMessage)
{
    logNoteOnComponent("TupcLom saves the addresses based from the sender and receiver of this message.\n"
                       "The receiver of this message is the address of TupcCm and this address will be the only active TupcLom instance and TupcCm instance.\n"
                       "The sender of this message is the address of OAM and this as the address of TupcIlm as well.\n");
    SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage(convertGenericToSpecificStatic<MessageName::OAM_ATM_HW_CONFIGURATION_MSG>(genericMessage));
    TAaSysComSicad senderSicad(AddressHelper::getAddress(hwConfigurationMessage.getSender()));
    TAaSysComSicad receiverSicad(AddressHelper::getAddress(hwConfigurationMessage.getReceiver()));
    m_oamAddress =  senderSicad;
    m_tupcIlmAddress = AddressHelper::createSicad(AddressHelper::getNid(senderSicad), AddressHelper::getTask(ComponentName::TupcIlm));
    m_tupcCmAddress = AddressHelper::createSicad(AddressHelper::getNid(receiverSicad), AddressHelper::getTask(ComponentName::TupcCm));
}

void TupcLom::handleTcomDeploymentMessage(GenericMessage const& genericMessage)
{
    SpecificStaticMessage<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG> message(convertGenericToSpecificStatic<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG>(genericMessage));
    STcomDeploymentIndMsg const& payload(message.getPayloadReference());
    AddressHelper::TAaSysComNids rlhNids(AddressHelper::getRlhNids(payload.wamAddressInd));
    for(TAaSysComNid const rlhNid : rlhNids)
    {
        TAaSysComSicad tupcTbmAddress(AddressHelper::createSicad(rlhNid, AddressHelper::getTask(ComponentName::TupcTbm)));
        sendTupcTbmConfigurationMsg(tupcTbmAddress);
    }
}

void TupcLom::sendTupcTbmConfigurationMsg(TAaSysComSicad const ) const
{
    Environment & environment(Environment::getInstance());
    SpecificStaticMessage<MessageName::TUPC_TBM_CONFIGURATION_MSG> specificMessage;
    STupcTbmConfigurationMsg & payload(specificMessage.getPayloadReference());
    payload.tupcCmSicad = m_tupcCmAddress;
    send(ComponentName::TupcTbm, convertSpecificStaticToGeneric<MessageName::TUPC_TBM_CONFIGURATION_MSG>(specificMessage));
    logNoteOnPreviousMessage("TupcLom sends TUPC_TBM_CONFIGURATION_MSG to TupcTbm.");
}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::OAM_ATM_HW_CONFIGURATION_MSG:
        handleHwConfigurationMessage(genericMessage);
        break;
    case MessageName::TC_TCOM_DEPLOYMENT_IND_MSG:
        handleTcomDeploymentMessage(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<endl;
        break;
    }
}

void TupcLom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

void TupcLom::handleOtherEvent(OtherEvent const& otherEvent)
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


/*
    //TUP_TbmConfigurationCmd //new message for TBM?
    //rename all of this shit.
    //const TMessageId TUP_CmConfigurationCmd_Msg = ATM_MESSAGE_BASE + 0x0118;
    //const TMessageId TUP_CmConfigurationResp_Msg = ATM_MESSAGE_BASE + 0x0119;
    //const TMessageId TUP_FspInfoUpdatedInd_Msg = ATM_MESSAGE_BASE + 0x011A;
    //const TMessageId TUP_FspInfoUpdatedIndResp_Msg = ATM_MESSAGE_BASE + 0x011B;
*/
}
