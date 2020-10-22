#include <Common/Environment.hpp>
#include <Common/Utils/EnumHelper.hpp>
#include <iostream>

using namespace std;

namespace DesignDocumentCreator
{

void Environment::execute()
{
    m_components.executePendingEvents();
}

Components& Environment::getComponentReference()
{
    return m_components;
}

void Environment::send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message)
{
    GenericMessage messageToRoute(message);
    messageToRoute.setSender(sender);
    messageToRoute.setReceiver(receiver);
    Component* receiverComponent = m_components.getComponentPointer(receiver);
    if(nullptr == receiverComponent)
    {
        cout<<"Message: ["<<EnumHelper::convertToString(message.getMessageName())<<"] sent to invalid component: ["<<EnumHelper::convertToString(receiver)<<"]"<<endl;
    }
    else
    {
        receiverComponent->pushBackEvent(Event(messageToRoute));
    }
}

}
