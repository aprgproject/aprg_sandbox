#pragma once

#include<Messages/Messages.hpp>
#include<Timers/Timers.hpp>

namespace DesignDocumentCreator
{

enum EventType
{
    MessageEvent,
    TimerEvent
};

class Event
{
public:
    Event(GenericMessage const& message);
    Event(Timer const& timer);

    EventType getType() const;
    Timer getTimer() const;
    GenericMessage getMessage() const;

private:
    EventType m_eventType;
    Timer m_timer;
    GenericMessage m_message;
};

}
