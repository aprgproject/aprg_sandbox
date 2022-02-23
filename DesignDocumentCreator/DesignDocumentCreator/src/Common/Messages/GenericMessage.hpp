#pragma once

#include <Common/Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageName.hpp>

namespace DesignDocumentCreator
{
class GenericMessage : public Message
{
public:    GenericMessage()
        : Message(MessageName::Empty)
    {}
    GenericMessage(MessageName const messageName, void* payloadBuffer, unsigned int const payloadSize)
        : Message(messageName)
        , m_payloadBuffer(payloadBuffer, payloadSize)
    {}
    GenericMessage(MessageName const messageName, alba::AlbaMemoryBuffer const& buffer, ComponentName const sender, ComponentName const receiver)
        : Message(messageName, sender, receiver)
        , m_payloadBuffer(buffer)
    {}
    GenericMessage(MessageName const messageName, void* payloadBuffer, unsigned int const payloadSize, ComponentName const sender, ComponentName const receiver)
        : Message(messageName, sender, receiver)
        , m_payloadBuffer(payloadBuffer, payloadSize)
    {}
    alba::AlbaMemoryBuffer& getPayloadBufferReference()
    {
        return m_payloadBuffer;
    }
    alba::AlbaMemoryBuffer const& getPayloadBufferConstReference() const
    {
        return m_payloadBuffer;
    }

private:
    alba::AlbaMemoryBuffer m_payloadBuffer;
};

}
