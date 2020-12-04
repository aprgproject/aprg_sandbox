#include <Common/Components/Component.hpp>

#include <Common/Utils/StringHelpers.hpp>

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator
{

Component::Component(ComponentName const componentName)
    : m_componentName(componentName)
    , m_componentNameInString(convertToString(componentName))
{}

void Component::pushBackEvent(Event const& event)
{
    m_eventQueue.push_back(event);
}

void Component::handleOneEvent()
{
    if(!isEventQueueEmpty())
    {
        handleEvent(m_eventQueue.front());
        m_eventQueue.pop_front();
    }
}

void Component::handleAllEvents()
{
    while(!isEventQueueEmpty())
    {
        handleOneEvent();
    }
}

bool Component::isEventQueueEmpty() const
{
    return m_eventQueue.empty();
}

GenericMessage Component::peekMessageAtStartOfTheEventQueue() const
{
    return GenericMessage(m_eventQueue.front().getMessage());
}

ComponentName Component::getComponentName() const
{
    return m_componentName;
}

string Component::getComponentNameInString() const
{
    return m_componentNameInString;
}

string Component::getQueueAsString() const
{
    return accumulate(m_eventQueue.begin(), m_eventQueue.end(), string("Event Queue: "), [](string const& partialResult, Event const& event)
    {
        return partialResult+event.getString()+", ";
    });
}

void Component::handleEvent(Event const& event)
{
    EventType eventType(event.getType());
    switch(eventType)
    {
    case EventType::MessageEvent:
        handleMessageEvent(event.getMessage());
        break;
    case EventType::TimerEvent:
        handleTimerEvent(event.getTimer());
        break;
    case EventType::OtherEvent:
        handleOtherEvent(event.getOtherEvent());
        break;
    }
}
void Component::handleMessageEvent(GenericMessage const& genericMessage)
{
    cout<<"Message event not handled. MessageName: "<<(int)genericMessage.getMessageName()<<endl;}

void Component::handleTimerEvent(Timer const& timer)
{
    cout<<"Timer event not handled. Type: "<<(int)timer.getType()<<" Id:"<<(int)timer.getId()<<endl;
}

void Component::handleOtherEvent(OtherEvent const& otherEvent)
{
    cout<<"Timer event not handled. Type: "<<(int)otherEvent.getType()<<endl;
}
}