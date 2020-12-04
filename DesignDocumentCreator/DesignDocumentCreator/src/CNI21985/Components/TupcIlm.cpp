#include "TupcIlm.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcIlm::TupcIlm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcIlm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
    }
}

void TupcIlm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

 void TupcIlm::handleOtherEvent(OtherEvent const& otherEvent)
{
    Environment& environment(Environment::getInstance());
    UmlLogger& umlLogger(environment.getUmlLogger());
    switch(otherEvent.getType())
    {
    case OtherEventType::ProcessStartup:
        umlLogger.logNoteOnComponent(m_componentName, "TupcIlm starts when its deployed on board 0x1011 (same with legacy Aalman)");
        break;
    default:
        cout<<"No handler for handleOtherEvent "<<endl;
        break;
    }

}

}
