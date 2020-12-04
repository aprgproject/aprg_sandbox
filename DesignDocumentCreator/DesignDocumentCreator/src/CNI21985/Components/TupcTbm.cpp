#include "TupcTbm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TupcTbm::TupcTbm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcTbm::handleStartup()
{
    logNoteOnComponent("TupcTbm **automatically**  starts when TUPCexe starts.");
}

void TupcTbm::handleMessageEvent(GenericMessage const& genericMessage){
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
    }
}

void TupcTbm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

void TupcTbm::handleOtherEvent(OtherEvent const& otherEvent)
{
   switch(otherEvent.getType())
   {
   case OtherEventType::MainProcessStartup:
       handleStartup();
       break;
   default:
       cout<<"No handler for handleOtherEvent "<<endl;
       break;
   }
}

}
