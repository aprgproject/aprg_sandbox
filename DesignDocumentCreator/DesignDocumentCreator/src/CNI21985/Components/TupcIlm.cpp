#include "TupcIlm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcIlm::TupcIlm()
{}

TupcIlm::TupcIlm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcIlm::handleMessageEvent(GenericMessage const& genericMessage){
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"No handler for messageName: "<<convertToString(genericMessage.getMessageName())<<endl;
    }
}

void TupcIlm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

}
