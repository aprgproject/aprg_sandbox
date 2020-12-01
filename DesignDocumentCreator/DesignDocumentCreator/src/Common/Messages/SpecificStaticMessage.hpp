#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
class SpecificStaticMessage
{
public:
    typedef MessageWrapper<messageName> SpecificStaticMessageWrapper;
    typedef typename SpecificStaticMessageWrapper::SackType SackType;
    SpecificStaticMessage()
        : m_sender(ComponentName::Empty)
        , m_receiver(ComponentName::Empty)
    {}
    MessageName getMessageName() const
    {
        return SpecificStaticMessageWrapper::getMessageName();
    }
    SackType& getPayloadReference()
    {
        return m_payload;
    }    ComponentName getSender() const
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
    SackType m_payload;
};

}