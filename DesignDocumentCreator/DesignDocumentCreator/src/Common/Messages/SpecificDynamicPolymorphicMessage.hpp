#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName, typename DynamicPartSackType>
class SpecificDynamicPolymorphicMessage
{
public:
    typedef MessageWrapper<messageName> SpecificDynamicPolymorphicMessageWrapper;
    typedef typename SpecificDynamicPolymorphicMessageWrapper::StaticPartSackType StaticPartSackType;
    SpecificDynamicPolymorphicMessage()
        : m_sender(ComponentName::Empty)
        , m_receiver(ComponentName::Empty)
    {}
    MessageName getMessageName() const
    {
        return SpecificDynamicPolymorphicMessageWrapper::getMessageName();
    }
    StaticPartSackType& getStaticPayloadReference()
    {
        return m_staticPayload;
    }
    DynamicPartSackType& getDynamicPayloadReference()
    {
        return m_dynamicPayload;
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
    DynamicPartSackType m_dynamicPayload;
};

}
