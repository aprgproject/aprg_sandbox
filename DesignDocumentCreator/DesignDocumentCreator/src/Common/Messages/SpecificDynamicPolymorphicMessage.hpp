#pragma once

#include <Memory/AlbaMemoryBuffer.hpp>
#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName, typename DynamicPartSackType>
class SpecificDynamicPolymorphicMessage : public Message
{
public:
    typedef MessageWrapper<messageName> SpecificDynamicPolymorphicMessageWrapper;
    typedef typename SpecificDynamicPolymorphicMessageWrapper::MessageDynamicPolymorphicSackType SackType;
    typedef typename SpecificDynamicPolymorphicMessageWrapper::DynamicPlaceHolderSackType DynamicPlaceHolderSackType;
    SpecificDynamicPolymorphicMessage()
        : Message(SpecificDynamicPolymorphicMessageWrapper::getMessageName())
    {}
    SpecificDynamicPolymorphicMessage(alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificDynamicPolymorphicMessageWrapper::getMessageName(), sender, receiver)
    {
        saveStaticAndDynamicPartFromBuffer(payloadBufferReference);
    }
    SackType& getStaticPayloadReference()
    {
        return m_staticPayload;
    }
    DynamicPartSackType& getDynamicPayloadReference()
    {
        return m_dynamicPayload;
    }
    alba::AlbaMemoryBuffer createBuffer() const
    {
        return createBufferFromStaticAndDynamicPart();
    }

private:
    void saveStaticAndDynamicPartFromBuffer(alba::AlbaMemoryBuffer const& payloadBufferReference)
    {
        alba::AlbaMemoryBuffer readingBuffer(payloadBufferReference);
        unsigned int maxSizeForReading(std::max(std::max(calculateSize(), payloadBufferReference.getSize()), sizeof(SackType)));
        readingBuffer.resize(maxSizeForReading);
        unsigned char* readingBufferPointer(reinterpret_cast<unsigned char*>(readingBuffer.getBufferPointer()));
        m_staticPayload = *reinterpret_cast<SackType*>(readingBufferPointer);
        readingBufferPointer+=calculateOffsetDynamicPart();
        m_dynamicPayload = *reinterpret_cast<DynamicPartSackType*>(readingBufferPointer);
    }
    alba::AlbaMemoryBuffer createBufferFromStaticAndDynamicPart() const
    {
        SackType payload(m_staticPayload);
        alba::AlbaMemoryBuffer buffer(&payload, calculateSize());
        unsigned char* writingBufferPointer(reinterpret_cast<unsigned char*>(buffer.getBufferPointer()));
        writingBufferPointer+=calculateOffsetDynamicPart();
        DynamicPartSackType* copyPointer = reinterpret_cast<DynamicPartSackType*>(writingBufferPointer);
        *copyPointer = m_dynamicPayload;
        return buffer;
    }
    unsigned int calculateOffsetDynamicPart() const
    {
        return sizeof(SackType)-sizeof(DynamicPlaceHolderSackType);
    }
    unsigned int calculateSize() const
    {
        return sizeof(SackType)-sizeof(DynamicPlaceHolderSackType)+sizeof(DynamicPartSackType);
    }
    SackType m_staticPayload;
    DynamicPartSackType m_dynamicPayload;
};

}
