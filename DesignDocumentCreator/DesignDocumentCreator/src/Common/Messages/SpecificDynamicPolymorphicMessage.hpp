#pragma once

#include <Common/Messages/Message.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator{

template<MessageName messageName, typename DynamicPartSackType>
class SpecificDynamicPolymorphicMessage : public Message
{
public:
    typedef MessageWrapper<messageName> SpecificDynamicPolymorphicMessageWrapper;
    typedef typename SpecificDynamicPolymorphicMessageWrapper::StaticPartSackType StaticPartSackType;
    SpecificDynamicPolymorphicMessage()
    {}
    MessageName getMessageName() const override
    {
        return SpecificDynamicPolymorphicMessageWrapper::getMessageName();
    }    StaticPartSackType& getStaticPayloadReference()
    {
        return m_staticPayload;
    }
    DynamicPartSackType& getDynamicPayloadReference()
    {
        return m_dynamicPayload;
    }

private:
    StaticPartSackType m_staticPayload;
    DynamicPartSackType m_dynamicPayload;
};
}
