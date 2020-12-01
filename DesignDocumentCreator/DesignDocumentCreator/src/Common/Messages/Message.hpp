#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>


namespace DesignDocumentCreator
{

class Message
{
public:
    Message()
        : m_sender(ComponentName::Empty)
        , m_receiver(ComponentName::Empty)
    {}
    Message(ComponentName const sender, ComponentName const receiver)
        : m_sender(sender)
        , m_receiver(receiver)
    {}
    virtual MessageName getMessageName() const;
    ComponentName getSender() const
    {
        return m_sender;
    }
    ComponentName getReceiver() const
    {
        return m_receiver;
    }\
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
};

}
