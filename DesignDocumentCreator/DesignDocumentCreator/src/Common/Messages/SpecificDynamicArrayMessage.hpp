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
    typedef MessageWrapper<messageName> SpecificDynamicArrayMessageWrapper;
    typedef typename SpecificDynamicArrayMessageWrapper::MessageDynamicArraySackType SackType;
    typedef typename SpecificDynamicArrayMessageWrapper::DynamicPartSackType DynamicPartSackType;
    SpecificDynamicArrayMessage()
        : Message(SpecificDynamicArrayMessageWrapper::getMessageName())
    {}
    SpecificDynamicArrayMessage(alba::AlbaMemoryBuffer const& payloadBufferReference, ComponentName const sender, ComponentName const receiver)
        : Message(SpecificDynamicArrayMessageWrapper::getMessageName(), sender, receiver)
    {
        saveStaticAndDynamicPartFromBuffer(payloadBufferReference);
    }
    SackType& getStaticPayloadReference()
    {
        return m_staticPayload;    }
    DynamicPartSackType& getDynamicPayloadReferenceAt(unsigned int position)
    {
        assert(position<dynamicPayloadItemSize);        return m_dynamicArrayPayload[position];
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
        DynamicPartSackType* copyPointer = reinterpret_cast<DynamicPartSackType*>(readingBufferPointer);
        for(DynamicPartSackType & dynamicArrayContent : m_dynamicArrayPayload)
        {
            dynamicArrayContent = *copyPointer;
            copyPointer++;
        }
    }
    alba::AlbaMemoryBuffer createBufferFromStaticAndDynamicPart() const
    {
        SackType payload(m_staticPayload);
        alba::AlbaMemoryBuffer buffer(&payload, calculateSize());
        unsigned char* writingBufferPointer(reinterpret_cast<unsigned char*>(buffer.getBufferPointer()));
        writingBufferPointer+=calculateOffsetDynamicPart();
        DynamicPartSackType* copyPointer = reinterpret_cast<DynamicPartSackType*>(writingBufferPointer);
        for(DynamicPartSackType const& dynamicArrayContent : m_dynamicArrayPayload)
        {
            *copyPointer = dynamicArrayContent;
            copyPointer++;
        }
        return buffer;
    }
    unsigned int calculateOffsetDynamicPart() const
    {
        return sizeof(SackType)+((int)-1*sizeof(DynamicPartSackType));
    }
    unsigned int calculateSize() const
    {
        return sizeof(SackType)+(((int)dynamicPayloadItemSize-1)*sizeof(DynamicPartSackType));
    }
    SackType m_staticPayload;
    std::array<DynamicPartSackType, dynamicPayloadItemSize> m_dynamicArrayPayload;
};

}
