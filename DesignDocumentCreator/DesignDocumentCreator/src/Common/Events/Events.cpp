#include "Events.hpp"

#include <Common/Utils/StringHelpers.hpp>

using namespace std;

namespace DesignDocumentCreator
{

Event::Event(GenericMessage const& message)
    : m_eventType(EventType::MessageEvent)
    , m_message(message)
{}

Event::Event(Timer const& timer)
    : m_eventType(EventType::TimerEvent)
    , m_timer(timer)
{}

EventType Event::getType() const
{
    return m_eventType;
}

Timer Event::getTimer() const
{
    return m_timer;
}

string Event::getString() const
{
    string result;
    switch(m_eventType)
    {
    case EventType::MessageEvent:
        result = StringHelpers::convertToString(m_message.getMessageName());
        break;
    case EventType::TimerEvent:
        result = StringHelpers::convertToString(m_timer.getType());
        break;
    }
    return result;
}

GenericMessage Event::getMessage() const
{
    return m_message;
}

}
