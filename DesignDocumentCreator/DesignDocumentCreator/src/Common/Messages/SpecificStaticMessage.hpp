#pragma once

#include <Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
class SpecificStaticMessage : public Message
{
public:
    typedef MessageWrapper<messageName> SpecificStaticMessageWrapper;
    typedef typename SpecificStaticMessageWrapper::MessageStaticSackType SackType;
    SpecificStaticMessage()
        : Message(SpecificStaticMessageWrapper::getMessageName())
    {}
    SpecificStaticMessage(alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificStaticMessageWrapper::getMessageName(), sender, receiver)
    {
        assert(sizeof(SackType) == payloadBufferReference.getSize());
        m_payload = *reinterpret_cast<SackType const*>(payloadBufferReference.getConstantBufferPointer());
    }
    SackType& getPayloadReference()
    {
        return m_payload;    }
    alba::AlbaMemoryBuffer createBuffer() const
    {
        return createBufferFromStaticPayload();    }

private:
    alba::AlbaMemoryBuffer createBufferFromStaticPayload() const
    {
        SackType payload(m_payload);
        return alba::AlbaMemoryBuffer(&payload, sizeof(payload));
    }
    SackType m_payload;
};

}
