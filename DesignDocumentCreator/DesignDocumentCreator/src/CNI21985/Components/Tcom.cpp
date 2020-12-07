#include "Tcom.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>
using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Tcom::Tcom(ComponentName const componentName)
    : Component(componentName)
{}

void Tcom::sendHwConfigurationResponseAck() const
{
    Environment & environment(Environment::getInstance());
    SpecificStaticMessage<MessageName::TC_HW_CONFIGURATION_RESP_MSG> specificMessage;
    SHwConfigurationResponseMsg & payload(specificMessage.getPayloadReference());
    payload.status = EStatus_NoError;
    environment.send(ComponentName::Tcom, ComponentName::Oam, convertSpecificStaticToGeneric<MessageName::TC_HW_CONFIGURATION_RESP_MSG>(specificMessage));
    logNoteOnPreviousMessage("TCOM/TOAM sends positive ack to OAM.");
}

void Tcom::handleHwConfigurationMessage(GenericMessage const& genericMessage) const
{
    logNoteOnPreviousMessage("TCOM/TOAM receives hardware cofiguration from OAM");
    SpecificStaticMessage<MessageName::TC_HW_CONFIGURATION_MSG> message(convertGenericToSpecificStatic<MessageName::TC_HW_CONFIGURATION_MSG>(genericMessage));
    //SHwConfigurationMsg const& payload(message.getPayloadReference());

    sendHwConfigurationResponseAck();
}

void Tcom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_HW_CONFIGURATION_MSG:
        handleHwConfigurationMessage(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
    }}

void Tcom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
