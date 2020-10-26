#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

Environment::Environment()
{}

void Environment::execute()
{
    m_components.executePendingEvents();
}

Components& Environment::getComponentReference()
{
    return m_components;
}

UmlLogger& Environment::getUmlLogger()
{
    return m_umlLogger;
}

void Environment::send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message)
{
    GenericMessage messageToRoute(message);
    messageToRoute.setSender(sender);
    messageToRoute.setReceiver(receiver);
    Component* receiverComponent = m_components.getComponentPointer(receiver);
    if(nullptr == receiverComponent)
    {
        cout<<"Message: ["<<StringHelpers::convertToString(message.getMessageName())<<"] sent to invalid component: ["<<StringHelpers::convertToString(receiver)<<"]"<<endl;
    }
    else
    {
        m_umlLogger.logMessage(StringHelpers::convertToString(sender), StringHelpers::convertToString(receiver), StringHelpers::convertToString(message.getMessageName()));
        receiverComponent->pushBackEvent(Event(messageToRoute));
    }
}

}


