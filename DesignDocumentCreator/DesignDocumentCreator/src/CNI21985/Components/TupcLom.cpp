#include "TupcLom.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{
TupcLom::TupcLom()
    : m_componentName(ComponentName::Empty)
{}

TupcLom::TupcLom(ComponentName const componentName)
    : m_componentName(componentName)
{}

void TupcLom::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"No handler for messageName: "<<convertToString(genericMessage.getMessageName())<<endl;
    }
}

void TupcLom::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}