#pragma once

#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

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
    SackType& getStaticPayloadReference()
    {
        return m_payload;
    }
    alba::AlbaMemoryBuffer createBuffer() const
    {
        return createBufferFromStaticPayload();
    }

private:
    alba::AlbaMemoryBuffer createBufferFromStaticPayload() const
    {
        return alba::AlbaMemoryBuffer(&m_payload, sizeof(m_payload));
    }
    SackType m_payload;
};

}
