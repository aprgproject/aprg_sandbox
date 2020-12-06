#include "TOAM.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

TOAM::TOAM(ComponentName const componentName)
    : Component(componentName)
{}

void TOAM::handleMessage1(GenericMessage const& genericMessage)
{
    cout<<"handleMessage1()"<<endl;
    Environment & environment(Environment::getInstance());

    SpecificStaticMessage<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG> message(convertGenericToSpecificStatic<MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG>(genericMessage));
    SLrmConfigurationDataInd& payload(message.getPayloadReference());
    logNoteOnPreviousMessage("Message 1 description.");
    logNoteOnComponent("TOAM will do something.");
}

void TOAM::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::TC_LRM_CONFIGURATION_DATA_IND_MSG:
        handleMessage1(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<". Please create one!"<<endl;
        break;
    }
}

void TOAM::handleTimerEvent(Timer const& timer)
{
    switch(timer.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle Timer, Empty: "<<endl;
    //    break;
    default:
        cout<<"No handler for timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<". Please create one!"<<endl;
        break;
    }
}

void TOAM::handleOtherEvent(OtherEvent const& otherEvent)
{
    switch(otherEvent.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle OtherEvent, Empty: "<<endl;
    //    break;
    default:
        cout<<"No handler for otherEventType: "<<(int)otherEvent.getType()<<". Please create one!"<<endl;
        break;
    }
}

}
