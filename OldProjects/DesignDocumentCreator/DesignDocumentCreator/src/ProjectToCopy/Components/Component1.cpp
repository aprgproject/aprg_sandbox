#include "Component1.hpp"

#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Component1::Component1(ComponentName const componentName)
    : Component(componentName)
{}

void Component1::handleMessage1(GenericMessage const& genericMessage)
{
    cout<<"handleMessage1()\n";
    Environment & environment(Environment::getInstance());

    SpecificStaticMessage<MessageName::MESSAGE_1> message(convertGenericToSpecificStatic<MessageName::MESSAGE_1>(genericMessage));    Message1Structure& payload(message.getStaticPayloadReference());
    logNoteOnPreviousMessage("Message 1 description.");
    logNoteOnComponent("Component1 will do something.");
}
void Component1::handleMessageEvent(GenericMessage const& genericMessage)
{
    MessageName messageName(genericMessage.getMessageName());
    switch(messageName)
    {
    case MessageName::MESSAGE_1:
        handleMessage1(genericMessage);
        break;
    default:
        cout<<"No handler for messageName: "<<genericMessage.getMessageNameInString()<<" in component: "<<getComponentNameInString()<<"\n";
        break;
    }
}
void Component1::handleTimerEvent(Timer const& timer)
{
    switch(timer.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle Timer, Empty: \n";
    //    break;
    default:
        cout<<"No handler for timerType: "<<convertToString(timer.getType())<<" timerId:"<<(int)timer.getId()<<". Please create one!\n";
        break;
    }
}
void Component1::handleOtherEvent(OtherEvent const& otherEvent)
{
    switch(otherEvent.getType())
    {
    //case TimerType::Empty:
    //    cout<<"Handle OtherEvent, Empty: \n";
    //    break;
    default:
        cout<<"No handler for otherEventType: "<<(int)otherEvent.getType()<<". Please create one!\n";
        break;
    }
}
}