#pragma once

#include<deque>
#include<Events/Events.hpp>
#include<Messages/Messages.hpp>
#include<Timers/Timers.hpp>

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
