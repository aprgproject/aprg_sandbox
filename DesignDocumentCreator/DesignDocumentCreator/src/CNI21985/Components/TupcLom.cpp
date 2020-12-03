#include "TupcLom.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>
#include <Utils/AddressHelper.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcLom::TupcLom(ComponentName const componentName)
    : Component(componentName)
{}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
        case MessageName::OAM_ATM_HW_CONFIGURATION_MSG:
            handleHwConfiguration(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
        break;
    }
}

void TupcLom::handleHwConfiguration(GenericMessage const& genericMessage)
{
    Environment& environment(Environment::getInstance());
    UmlLogger& umlLogger(environment.getUmlLogger());

    cout<<"Handle Message, OAM_ATM_HW_CONFIGURATION_MSG: "<<endl;
    SpecificStaticMessage<MessageName::OAM_ATM_HW_CONFIGURATION_MSG> hwConfigurationMessage(convertGenericToSpecificStatic<MessageName::OAM_ATM_HW_CONFIGURATION_MSG>(genericMessage));
    SAtmHwConfigurationMsgFake& payload(hwConfigurationMessage.getPayloadReference());
    m_oamAddress = AddressHelper::getAddress(hwConfigurationMessage.getSender());
    umlLogger.logNoteOnComponent(getComponentName(), R"(TupcLom handles Hw Configuration)");
}

void TupcLom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
