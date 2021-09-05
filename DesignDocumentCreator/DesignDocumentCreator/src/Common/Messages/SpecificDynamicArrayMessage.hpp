#pragma once

#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

#include <vector>

namespace DesignDocumentCreator
{

template<MessageName messageName>
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
        return m_staticPayload;
    }
    void addDynamicPart(DynamicPartSackType const& dynamicPart)
    {
        m_dynamicArrayPayload.emplace_back(dynamicPart);
    }
    DynamicPartSackType& getDynamicPayloadReferenceAtAndCreateIfNeeded(unsigned int const position)
    {
        if(position+1>m_dynamicArrayPayload.size())
        {
            m_dynamicArrayPayload.resize(position+1);
        }
        return m_dynamicArrayPayload[position];
    }
    alba::AlbaMemoryBuffer createBuffer() const
    {
        return createBufferFromStaticAndDynamicPart();
    }

private:
    void saveStaticAndDynamicPartFromBuffer(alba::AlbaMemoryBuffer const& payloadBufferReference)
    {
        unsigned char const*  readingBufferPointer(reinterpret_cast<unsigned char const*>(payloadBufferReference.getConstantBufferPointer()));
        m_staticPayload = *reinterpret_cast<SackType const*>(readingBufferPointer);
        DynamicPartSackType const*  copyPointerStart=reinterpret_cast<DynamicPartSackType const*>(readingBufferPointer+calculateOffsetForDynamicPart());
        DynamicPartSackType const* const copyPointerEnd=reinterpret_cast<DynamicPartSackType const*>(readingBufferPointer+payloadBufferReference.getSize());
        for(DynamicPartSackType const* copyPointer=copyPointerStart; copyPointer<copyPointerEnd; copyPointer++)
        {
            m_dynamicArrayPayload.emplace_back(*copyPointer);
        }
    }
    alba::AlbaMemoryBuffer createBufferFromStaticAndDynamicPart() const
    {
        alba::AlbaMemoryBuffer buffer(&m_staticPayload, calculateOffsetForDynamicPart());
        for(DynamicPartSackType const& dynamicArrayContent : m_dynamicArrayPayload)
        {
            buffer.addData(&dynamicArrayContent,  sizeof(DynamicPartSackType));
        }
        return buffer;
    }
    unsigned int calculateOffsetForDynamicPart() const
    {
        return sizeof(SackType)+((int)-1*sizeof(DynamicPartSackType));
    }
    SackType m_staticPayload;
    std::vector<DynamicPartSackType> m_dynamicArrayPayload;
};

}
