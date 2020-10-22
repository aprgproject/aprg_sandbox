#include "Component.hpp"
#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

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

bool Component::isEventQueueEmpty()
{
    return m_eventQueue.empty();
}

void Component::handleEvent(Event const& event)
{
    EventType eventType(event.getType());
    switch(eventType)
    {
    case MessageEvent:
        handleMessageEvent(event.getMessage());
        break;
    case TimerEvent:
        handleTimerEvent(event.getTimer());
        break;
    }
}

void Component::handleMessageEvent(GenericMessage const& genericMessage)
{
    cout<<"Message event not handled. MessageName: "<<(int)genericMessage.getMessageName()<<endl;
}

void Component::handleTimerEvent(Timer const& timer)
{
    cout<<"Timer event not handled. Type: "<<(int)timer.getType()<<" Id:"<<(int)timer.getId()<<endl;
}

}
