#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

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

void Environment::send(GenericMessage const& message)
{
    performSend(message);
}

void Environment::send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message)
{
    GenericMessage messageToRoute(message);
    messageToRoute.setSender(sender);
    messageToRoute.setReceiver(receiver);
    performSend(messageToRoute);
}

void Environment::performSend(GenericMessage const& messageToRoute)
{
    ComponentName receiver(messageToRoute.getReceiver());
    ComponentName sender(messageToRoute.getSender());
    MessageName messageName(messageToRoute.getMessageName());
    Component* receiverComponent = m_components.getComponentPointer(receiver);
    if(nullptr == receiverComponent)
    {
        cout<<"Message: ["<<convertToString(messageName)<<"] sent to invalid component: ["<<convertToString(receiver)<<"]"<<endl;
    }
    else
    {
        m_umlLogger.logMessage(convertToString(sender), convertToString(receiver), convertToString(messageName));
        receiverComponent->pushBackEvent(Event(messageToRoute));
    }
}
}
