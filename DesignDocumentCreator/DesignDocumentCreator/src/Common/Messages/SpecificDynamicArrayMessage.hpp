#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Messages/MessageWrapper.hpp>

#include <array>

namespace DesignDocumentCreator
{

template<MessageName messageName, unsigned int dynamicPayloadItemSize>
class SpecificDynamicArrayMessage
{
public:
    typedef MessageWrapper<messageName> SpecificDynamicArrayMessageWrapper;
    typedef typename SpecificDynamicArrayMessageWrapper::StaticPartSackType StaticPartSackType;
    typedef typename SpecificDynamicArrayMessageWrapper::DynamicPartSackType DynamicPartSackType;
    SpecificDynamicArrayMessage()
        : m_sender(ComponentName::Empty)
        , m_receiver(ComponentName::Empty)
    {}
    MessageName getMessageName() const
    {
        return SpecificDynamicArrayMessageWrapper::getMessageName();
    }
    StaticPartSackType& getStaticPayloadReference()
    {
        return m_staticPayload;
    }
    DynamicPartSackType& getDynamicPayloadReferenceAt(unsigned int position)
    {
        assert(position<dynamicPayloadItemSize);
        return m_dynamicArrayPayload[position];
    }
    ComponentName getSender() const
    {
        return m_sender;
    }
    ComponentName getReceiver() const
    {
        return m_receiver;
    }
    void setSender(ComponentName const sender)
    {
        m_sender = sender;
    }
    void setReceiver(ComponentName const receiver)
    {
        m_receiver = receiver;
    }


private:
    ComponentName m_sender;
    ComponentName m_receiver;
    StaticPartSackType m_staticPayload;
    std::array<DynamicPartSackType, dynamicPayloadItemSize> m_dynamicArrayPayload;
};

}
