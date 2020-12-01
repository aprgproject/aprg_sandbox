#pragma once

#include <Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator{

template<MessageName messageName>
class SpecificStaticMessage : public Message
{
public:
    typedef MessageWrapper<messageName> SpecificStaticMessageWrapper;
    typedef typename SpecificStaticMessageWrapper::SackType SackType;
    SpecificStaticMessage()
    {}
    SpecificStaticMessage(alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(sender, receiver)
    {
        assert(sizeof(SackType) == payloadBufferReference.getSize());
        m_payload = *reinterpret_cast<SackType const*>(payloadBufferReference.getConstantBufferPointer());
    }
    MessageName getMessageName() const override
    {
        return SpecificStaticMessageWrapper::getMessageName();
    }
    SackType& getPayloadReference()    {
        return m_payload;
    }

private:
    SackType m_payload;
};
}
