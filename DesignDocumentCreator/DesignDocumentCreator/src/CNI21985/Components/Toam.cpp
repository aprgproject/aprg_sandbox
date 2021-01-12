#include "Toam.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

void Toam::HwConfiguration::saveConfiguration(SHwConfigurationMsg const&)
{
    //this is fake
}

STCWamAddressIndNew Toam::HwConfiguration::generateWamAddressInd() const
{
    //this is fake
    return STCWamAddressIndNew();
}

Toam::Toam(ComponentName const componentName)
    : Component(componentName)
{}

void Toam::handleHwConfigurationMessage(GenericMessage const& genericMessage)
{
    logNoteOnPreviousMessage("TCOM/TOAM receives hardware cofiguration from OAM.");
    SpecificStaticMessage<MessageName::TC_HW_CONFIGURATION_MSG> message(convertGenericToSpecificStatic<MessageName::TC_HW_CONFIGURATION_MSG>(genericMessage));
    SHwConfigurationMsg const& payload(message.getPayloadReference());
    saveConfiguration(payload);
    sendHwConfigurationResponseAck();
}

void Toam::handleLinkStatesMessage(GenericMessage const& genericMessage) const
{
    logNoteOnPreviousMessage("TCOM/TOAM receives status of NBAP links from OAM.");
    SpecificStaticMessage<MessageName::TC_LINK_STATES_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LINK_STATES_MSG>(genericMessage));
    sendsLinkStatesResponse();
    log("alt if all links are up and previously some links were down");
    sendsTcomDeploymentInd();
    log("end alt");
}

void Toam::sendHwConfigurationResponseAck() const
{
    SpecificStaticMessage<MessageName::TC_HW_CONFIGURATION_RESP_MSG> specificMessage;
    SHwConfigurationResponseMsg & payload(specificMessage.getPayloadReference());
    payload.status = EStatus_NoError;
    send(ComponentName::Oam, convertSpecificStaticToGeneric<MessageName::TC_HW_CONFIGURATION_RESP_MSG>(specificMessage));
    logNoteOnPreviousMessage("TCOM/TOAM sends HW configuration ack to OAM.");
}

void Toam::sendsLinkStatesResponse() const
{
    SpecificStaticMessage<MessageName::TC_LINK_STATES_RESP_MSG> specificMessage;
    send(ComponentName::Oam, convertSpecificStaticToGeneric<MessageName::TC_LINK_STATES_RESP_MSG>(specificMessage));
    logNoteOnPreviousMessage("TCOM/TOAM sends Link states response to OAM.");
}

void Toam::sendsTcomDeploymentInd() const
{
    SpecificStaticMessage<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG> specificMessage;
    STcomDeploymentIndMsg & payload(specificMessage.getPayloadReference());
    logNoteOnComponent("TCOM/TOAM generates wamAddressInd structure base from hardware configuration.");
    payload.wamAddressInd = m_configuration.generateWamAddressInd();
    send(ComponentName::TupcLom, convertSpecificStaticToGeneric<MessageName::TC_TCOM_DEPLOYMENT_IND_MSG>(specificMessage));
    logNoteOnPreviousMessage("TCOM/TOAM sends TCOM deployment message with wamAddressInd structure to TupcLom.");
}

void Toam::saveConfiguration(SHwConfigurationMsg const& hwConfigurationMsg)
{
    logNoteOnComponent("TCOM saves hardware configuration.");
    m_configuration.saveConfiguration(hwConfigurationMsg);
}

void Toam::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_HW_CONFIGURATION_MSG:
        handleHwConfigurationMessage(genericMessage);
        break;
    case MessageName::TC_LINK_STATES_MSG:
        handleLinkStatesMessage(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<endl;
    }
}

void Toam::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
