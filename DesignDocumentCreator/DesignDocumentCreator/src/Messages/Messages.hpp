#pragma once

#include <AlbaMemoryBuffer.hpp>
#include <cassert>
#include "MessageWrapper.hpp"
#include <Sacks/Sacks.hpp>
#include <string>

namespace DesignDocumentCreator
{

enum class MessageName
{
    MESSAGE_SAMPLE
};

WRAP_MESSAGE(MessageName::MESSAGE_SAMPLE, SampleSack)


template<MessageName messageName>
class SpecificMessage
{
public:
    typedef MessageWrapper<messageName> SpecificMessageWrapper;
    typedef typename SpecificMessageWrapper::SackType SpecificMessageSackType;
    MessageName getMessageName()
    {
        return SpecificMessageWrapper::getMessageName();
    }
    SpecificMessageSackType& getPayloadReference()
    {
        return m_payload;
    }

private:
    SpecificMessageSackType m_payload;
};


class GenericMessage
{
public:
    GenericMessage(MessageName messageName, void* payloadBuffer, unsigned int payloadSize)
        : m_messageName(messageName)
    {
        m_payloadBuffer.setBuffer(payloadBuffer, payloadSize);
    }
    MessageName getMessageName() const
    {
        return m_messageName;
    }
    alba::AlbaMemoryBuffer& getPayloadBufferReference()
    {
        return m_payloadBuffer;
    }

private:
    MessageName m_messageName;
    alba::AlbaMemoryBuffer m_payloadBuffer;
};

template<MessageName messageName>
SpecificMessage<messageName> convertGenericToSpecific(GenericMessage& genericMessage)
{
    SpecificMessage<messageName> specificMessage;
    typedef typename SpecificMessage<messageName>::SpecificMessageSackType SackType;
    SackType& payloadReference = specificMessage.getPayloadReference();
    alba::AlbaMemoryBuffer& payloadBufferReference = genericMessage.getPayloadBufferReference();
    assert(sizeof(SackType) == genericMessage.getPayloadBufferReference().getSize());
    payloadReference = *reinterpret_cast<SackType*>(payloadBufferReference.getBufferPointer());
    return specificMessage;
}

template<MessageName messageName>
GenericMessage convertSpecificToGeneric(SpecificMessage<messageName>& specificMessage)
{
    typedef typename SpecificMessage<messageName>::SpecificMessageSackType SackType;
    SackType& payloadReference = specificMessage.getPayloadReference();
    return GenericMessage(specificMessage.getMessageName(), &payloadReference, sizeof(SackType));
}

}
