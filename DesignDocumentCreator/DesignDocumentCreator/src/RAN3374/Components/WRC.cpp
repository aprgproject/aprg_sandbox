#include <Common/Utils/EnumHelper.hpp>
#include <iostream>
#include <RAN3374/Components/WRC.hpp>

using namespace std;

namespace DesignDocumentCreator
{

WRC::WRC()
    : m_componentName(ComponentName::EMPTY)
{}

WRC::WRC(ComponentName const componentName)
    : m_componentName(componentName)
{}

void WRC::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LTX_TELECOM_MSG:
        cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Handle Message, messageName: "<<EnumHelper::convertToString(genericMessage.getMessageName())<<endl;
    }
}

void WRC::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<EnumHelper::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
