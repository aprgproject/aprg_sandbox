#include "TupcCm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcCm::TupcCm()
    : m_componentName(ComponentName::Empty)
{}
TupcCm::TupcCm(ComponentName const componentName)
    : m_componentName(componentName)
{}

void TupcCm::handleMessageEvent(GenericMessage const& genericMessage)
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

void TupcCm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
