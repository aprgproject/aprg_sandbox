#pragma once

#include <Common/Messages/GenericMessage.hpp>
#include <Common/Messages/SpecificStaticMessage.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
SpecificStaticMessage<messageName> convertGenericToSpecificStatic(GenericMessage& genericMessage)
{
    SpecificStaticMessage<messageName> specificStaticMessage(genericMessage.getPayloadBufferConstReference(), genericMessage.getSender(), genericMessage.getReceiver());
    return specificStaticMessage;
}

template<MessageName messageName>
GenericMessage convertSpecificToGeneric(SpecificStaticMessage<messageName>& specificStaticMessage)
{
    typedef typename SpecificStaticMessage<messageName>::SackType SackType;
    SackType& payloadReference = specificStaticMessage.getPayloadReference();
    GenericMessage genericMessage(specificStaticMessage.getMessageName(), &payloadReference, sizeof(SackType), specificStaticMessage.getSender(), specificStaticMessage.getReceiver());
    return genericMessage;
}
}
