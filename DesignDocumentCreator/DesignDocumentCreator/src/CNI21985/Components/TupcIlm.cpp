#include "TupcIlm.hpp"

#include <Common/Utils/StringHelpers.hpp>

#include <iostream>
using namespace std;
using namespace DesignDocumentCreator::StringHelpers;
namespace DesignDocumentCreator
{

TupcIlm::TupcIlm(ComponentName const componentName)
    : Component(componentName)
{}

void TupcIlm::handleStartup()
{
    logNoteOnComponent("TupcIlm **starts_only**  when its deployed on board 0x10 or 0x20(for FSM r4).\nThis is same with legacy Aalman.");
    /*if(AaSysComNmapGetBoard(sicad) == FSM1_FCT || AaSysComNmapGetBoard(sicad) == FSM2_FCT)
    {
        StartAalman();
    }*/
}

void TupcIlm::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());    switch(messageName)
    {
    //case MessageName::TC_LTX_TELECOM_MSG:
    //    cout<<"Handle Message, TC_LTX_TELECOM_MSG: "<<endl;    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<endl;
    }
}

void TupcIlm::handleTimerEvent(Timer const& timer)
{
    cout<<"Handle Timer, timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<endl;
}

 void TupcIlm::handleOtherEvent(OtherEvent const& otherEvent)
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