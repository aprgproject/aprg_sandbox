#pragma once

#include <Components//ComponentName.hpp>
#include <Messages/MessageName.hpp>
#include <Messages/MessageWrapper.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
class SpecificMessage
{
public:
    typedef MessageWrapper<messageName> SpecificMessageWrapper;
    typedef typename SpecificMessageWrapper::SackType SpecificMessageSackType;
    SpecificMessage()
        : m_sender(ComponentName::EMPTY)
        , m_receiver(ComponentName::EMPTY)
    {}
    MessageName getMessageName() const
    {
        return SpecificMessageWrapper::getMessageName();
    }
    SpecificMessageSackType& getPayloadReference()
    {
        return m_payload;
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
    SpecificMessageSackType m_payload;
};

}
