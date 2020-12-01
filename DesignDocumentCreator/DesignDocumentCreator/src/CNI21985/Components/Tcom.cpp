#include "Tcom.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

Tcom::Tcom()
    : m_componentName(ComponentName::Empty)
{}

Tcom::Tcom(ComponentName const componentName)    : m_componentName(componentName)
{}

void Tcom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Cannot handle message messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
    }}

void Tcom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
