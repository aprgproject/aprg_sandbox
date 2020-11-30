#include "TupcLom.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

TupcLom::TupcLom()
    : m_componentName(ComponentName::EMPTY)
{}

TupcLom::TupcLom(ComponentName const componentName)
    : m_componentName(componentName)
{}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LTX_TELECOM_MSG:
        cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Cannot handle message messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
    }
}

void TupcLom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
