#include "Component1.hpp"

#include <Common/Utils/StringHelpers.hpp>
#include <iostream>

using namespace std;using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Component1::Component1(ComponentName const componentName)
    : Component(componentName)
{}

void Component1::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
    }
}

void Component1::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}
}