#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Utils/StringHelpers.hpp>

#include <string>

namespace DesignDocumentCreator {

class Message {
public:
    Message(MessageName const messageName)
        : m_messageName(messageName),
          m_sender(ComponentName::Empty),
          m_receiver(ComponentName::Empty),
          m_messageNameInString(StringHelpers::convertToString(messageName)) {}
    Message(MessageName const messageName, ComponentName const sender, ComponentName const receiver)
        : m_messageName(messageName),
          m_sender(sender),
          m_receiver(receiver),
          m_messageNameInString(StringHelpers::convertToString(messageName)) {}
    std::string getMessageNameInString() const { return m_messageNameInString; }
    MessageName getMessageName() const { return m_messageName; }
    ComponentName getSender() const { return m_sender; }
    ComponentName getReceiver() const { return m_receiver; }
    void setSender(ComponentName const sender) { m_sender = sender; }
    void setReceiver(ComponentName const receiver) { m_receiver = receiver; }

private:
    MessageName m_messageName;
    ComponentName m_sender;
    ComponentName m_receiver;
    std::string m_messageNameInString;
};

}  // namespace DesignDocumentCreator
