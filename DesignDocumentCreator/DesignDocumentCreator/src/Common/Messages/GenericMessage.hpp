#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>


namespace DesignDocumentCreator
{

class GenericMessage
{
public:
    GenericMessage()
        : m_messageName(MessageName::EMPTY)
    {}
    GenericMessage(MessageName const messageName, void* payloadBuffer, unsigned int const payloadSize)
        : m_messageName(messageName)
        , m_sender(ComponentName::EMPTY)
        , m_receiver(ComponentName::EMPTY)
        , m_payloadBuffer(payloadBuffer, payloadSize)
    {}

    MessageName getMessageName() const
    {
        return m_messageName;
    }
    ComponentName getSender() const
    {
        return m_sender;
    }
    ComponentName getReceiver() const
    {
        return m_receiver;
    }
    alba::AlbaMemoryBuffer& getPayloadBufferReference()
    {
        return m_payloadBuffer;
    }
    void setSender(ComponentName const sender)
    {
        m_sender = sender;
    }
    void setReceiver(ComponentName const receiver)
    {
        m_receiver = receiver;
    }

private:
    MessageName m_messageName;
    ComponentName m_sender;
    ComponentName m_receiver;
    alba::AlbaMemoryBuffer m_payloadBuffer;
};

}
