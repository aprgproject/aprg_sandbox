#pragma once

#include <Messages/GenericMessage.hpp>
#include <Messages/SpecificMessage.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
SpecificMessage<messageName> convertGenericToSpecific(GenericMessage& genericMessage)
{
    SpecificMessage<messageName> specificMessage;
    typedef typename SpecificMessage<messageName>::SpecificMessageSackType SackType;
    SackType& payloadReference = specificMessage.getPayloadReference();
    alba::AlbaMemoryBuffer& payloadBufferReference = genericMessage.getPayloadBufferReference();
    assert(sizeof(SackType) == genericMessage.getPayloadBufferReference().getSize());
    payloadReference = *reinterpret_cast<SackType*>(payloadBufferReference.getBufferPointer());
    specificMessage.setSender(genericMessage.getSender());
    specificMessage.setReceiver(genericMessage.getReceiver());
    return specificMessage;
}

template<MessageName messageName>
GenericMessage convertSpecificToGeneric(SpecificMessage<messageName>& specificMessage)
{
    typedef typename SpecificMessage<messageName>::SpecificMessageSackType SackType;
    SackType& payloadReference = specificMessage.getPayloadReference();
    GenericMessage genericMessage(specificMessage.getMessageName(), &payloadReference, sizeof(SackType));
    genericMessage.setSender(specificMessage.getSender());
    genericMessage.setReceiver(specificMessage.getReceiver());
    return genericMessage;
}

}
