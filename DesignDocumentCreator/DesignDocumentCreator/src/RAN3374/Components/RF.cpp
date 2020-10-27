#include <RAN3374/Components/RF.hpp>

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

RF::RF()
    : m_componentName(ComponentName::EMPTY)
{}

RF::RF(ComponentName const componentName)
    : m_componentName(componentName)
{}

void RF::handleMessageEvent(GenericMessage const& genericMessage)
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

void RF::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
