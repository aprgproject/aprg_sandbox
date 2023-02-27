#include "Oam.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Oam::Oam(ComponentName const componentName)
    : Component(componentName)
{}

void Oam::handleHwConfigurationMessageResponse(GenericMessage const&) const
{
    //I am not coding OAM. :)
}

void Oam::handleLinkStatesResponse(GenericMessage const&) const
{
    //I am not coding OAM. :)
}

void Oam::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_HW_CONFIGURATION_RESP_MSG:
        handleHwConfigurationMessageResponse(genericMessage);
        break;
    case MessageName::TC_LINK_STATES_RESP_MSG:
        handleLinkStatesResponse(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<"\n";
    }
}

void Oam::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<"\n";
}

}