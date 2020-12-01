#pragma once

#include <Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

#include <array>
namespace DesignDocumentCreator
{

template<MessageName messageName, unsigned int dynamicPayloadItemSize>
class SpecificDynamicArrayMessage : public Message
{
public:
    typedef MessageWrapper<messageName> SpecificDynamicArrayMessageWrapper;    typedef typename SpecificDynamicArrayMessageWrapper::StaticPartSackType StaticPartSackType;
    typedef typename SpecificDynamicArrayMessageWrapper::DynamicPartSackType DynamicPartSackType;
    SpecificDynamicArrayMessage()
    {}
    SpecificDynamicArrayMessage(alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(sender, receiver)
    {
        assert(sizeof(SackType) == payloadBufferReference.getSize());
        m_payload = *reinterpret_cast<SackType const*>(payloadBufferReference.getConstantBufferPointer());
    }
    MessageName getMessageName() const override
    {
        return SpecificDynamicArrayMessageWrapper::getMessageName();
    }
    StaticPartSackType& getStaticPayloadReference()    {
        return m_staticPayload;
    }
    DynamicPartSackType& getDynamicPayloadReferenceAt(unsigned int position)
    {
        assert(position<dynamicPayloadItemSize);
        return m_dynamicArrayPayload[position];
    }

private:
    StaticPartSackType m_staticPayload;
    std::array<DynamicPartSackType, dynamicPayloadItemSize> m_dynamicArrayPayload;
};
}
