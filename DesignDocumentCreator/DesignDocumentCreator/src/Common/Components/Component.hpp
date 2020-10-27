#pragma once

#include <Common/Events/Events.hpp>
#include <Common/Messages/Messages.hpp>
#include <Common/Timers/Timers.hpp>

#include <deque>

namespace DesignDocumentCreator
{

class Component
{
public:
    void pushBackEvent(Event const& event);
    void handleOneEvent();
    void handleAllEvents();
    bool isEventQueueEmpty();

protected:
    virtual void handleEvent(Event const& event);
    virtual void handleMessageEvent(GenericMessage const& genericMessage);
    virtual void handleTimerEvent(Timer const& timer);
    std::deque<Event> m_eventQueue;
};

}
