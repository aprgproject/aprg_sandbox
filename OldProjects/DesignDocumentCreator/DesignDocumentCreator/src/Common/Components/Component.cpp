#include "Component.hpp"

#include <Common/Environment.hpp>
#include <Common/Uml/UmlLogger.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <algorithm>
#include <iostream>
#include <numeric>
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

void Component::send(ComponentName const receiver, GenericMessage const& message) const
{
    Environment & environment(Environment::getInstance());
    environment.send(m_componentName, receiver, message);
}

bool Component::isEventQueueEmpty() const
{
    return m_eventQueue.empty();
}

GenericMessage Component::peekMessageAtStartOfTheEventQueue() const
{
    GenericMessage message;
    if(!isEventQueueEmpty())
    {
        message = GenericMessage(m_eventQueue.front().getMessage());
    }
    return message;
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

void Component::log(string const& line) const
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    umlLogger.log(line);
}

void Component::logNoteOnPreviousMessage(string const& note) const
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    umlLogger.logNoteOnPreviousMessage(note);
}

void Component::logNoteOnComponent(string const& note) const
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    umlLogger.logNoteOnComponent(m_componentName, note);
}

void Component::logNoteOnComponents(ComponentNames const& componentNames, string const& note) const
{
    UmlLogger& umlLogger(Environment::getInstance().getUmlLogger());
    umlLogger.logNoteOnComponents(componentNames, note);
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
    cout<<"Message event not handled. MessageName: "<<(int)genericMessage.getMessageName()<<"\n";
}

void Component::handleTimerEvent(Timer const& timer)
{
    cout<<"Timer event not handled. Type: "<<(int)timer.getType()<<" Id:"<<(int)timer.getId()<<"\n";
}

void Component::handleOtherEvent(OtherEvent const& otherEvent)
{
    cout<<"Timer event not handled. Type: "<<(int)otherEvent.getType()<<"\n";
}

}