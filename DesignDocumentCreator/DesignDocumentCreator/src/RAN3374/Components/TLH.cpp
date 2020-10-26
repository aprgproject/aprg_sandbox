#include <Common/Utils/StringHelpers.hpp>
#include <RAN3374/Components/TLH.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

TLH::TLH()
    : m_componentName(ComponentName::EMPTY)
{}

TLH::TLH(ComponentName const componentName)
    : m_componentName(componentName)
{}

void TLH::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LTX_TELECOM_MSG:
        cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Handle Message, messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
    }
}

void TLH::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}


