#include <Common/Events/Events.hpp>

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

GenericMessage Event::getMessage() const
{
    return m_message;
}

}
