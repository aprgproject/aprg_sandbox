#include <Common/Environment.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <iostream>

using namespace std;
using namespace DesignDocumentCreator::StringHelpers;

namespace DesignDocumentCreator {

Environment::Environment() { m_resetableMembers.emplace(); }

Environment& Environment::getInstance() {
    static Environment instance;
    return instance;
}

void Environment::clear() { m_resetableMembers.emplace(); }

void Environment::execute() { m_resetableMembers->components.executePendingEvents(); }

Components& Environment::getComponentsReference() { return m_resetableMembers->components; }

UmlLogger& Environment::getUmlLogger() { return m_resetableMembers->umlLogger; }

Component* Environment::getComponentPointer(ComponentName const componentName) {
    return getComponentsReference().getComponentPointer(componentName);
}

void Environment::send(GenericMessage const& message) { performSend(message); }

void Environment::send(ComponentName const sender, ComponentName const receiver, GenericMessage const& message) {
    GenericMessage messageToRoute(message);
    messageToRoute.setSender(sender);
    messageToRoute.setReceiver(receiver);
    performSend(messageToRoute);
}

void Environment::performSend(GenericMessage const& messageToRoute) {
    ComponentName receiver(messageToRoute.getReceiver());
    ComponentName sender(messageToRoute.getSender());
    string senderNameString(convertToString(sender));
    string receiverNameString(convertToString(receiver));
    Component* receiverComponent = getComponentPointer(receiver);
    if (nullptr == receiverComponent) {
        cout << "[" << senderNameString << "] sends the message [" << messageToRoute.getMessageNameInString()
             << "] to an invalid receiver [" << receiverNameString << "]\n";
    } else {
        cout << "[" << senderNameString << "] sends the message [" << messageToRoute.getMessageNameInString()
             << "] to [" << receiverNameString << "]\n";
        getUmlLogger().logMessage(senderNameString, receiverNameString, messageToRoute.getMessageNameInString());
        receiverComponent->pushBackEvent(Event(messageToRoute));
    }
}

}  // namespace DesignDocumentCreator
