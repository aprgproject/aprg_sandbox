#include "TupcCm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcCm::TupcCm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcCm::handleTupcExeStartup()
{
    logNoteOnComponent("TupcCm is **not_automatically**  started when TUPCexe starts.\nThis is same with legacy Conman.");
}

void TupcCm::handleTupcCmStartup()
{
    logNoteOnComponent("TupcCm is **started**.");
}

void TupcCm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<endl;
    }
}

void TupcCm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

void TupcCm::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleTupcExeStartup();
       break;
   case OtherEventType::SubProcessStartup:
       handleTupcCmStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent "<<endl;
       break;
   }
}

}
