#include "TupcTbm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

TupcTbm::TupcTbm()
    : m_componentName(ComponentName::Empty)
{}

TupcTbm::TupcTbm(ComponentName const componentName)    : m_componentName(componentName)
{}

void TupcTbm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"Cannot handle message messageName: "<<StringHelpers::convertToString(genericMessage.getMessageName())<<endl;
    }}

void TupcTbm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<StringHelpers::convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
