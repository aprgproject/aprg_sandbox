#pragma once

#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

namespace DesignDocumentCreator
{

class GenericMessage : public Message
{
public:
    GenericMessage()        : m_messageName(MessageName::Empty)
    {}
    GenericMessage(MessageName const messageName, void* payloadBuffer, unsigned int const payloadSize)
        : m_messageName(messageName)
        , m_payloadBuffer(payloadBuffer, payloadSize)
    {}
    GenericMessage(MessageName const messageName, void* payloadBuffer, unsigned int const payloadSize, ComponentName const sender, ComponentName const receiver)
        : Message(sender, receiver)
        , m_messageName(messageName)
        , m_payloadBuffer(payloadBuffer, payloadSize)
    {}
    MessageName getMessageName() const override
    {
        return m_messageName;
    }
    alba::AlbaMemoryBuffer& getPayloadBufferReference()
    {
        return m_payloadBuffer;
    }
    alba::AlbaMemoryBuffer const& getPayloadBufferConstReference()
    {
        return m_payloadBuffer;
    }

private:
    MessageName m_messageName;
    alba::AlbaMemoryBuffer m_payloadBuffer;
};
}
