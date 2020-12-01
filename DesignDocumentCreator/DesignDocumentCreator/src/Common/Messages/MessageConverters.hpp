#pragma once

#include <Common/Messages/GenericMessage.hpp>
#include <Common/Messages/SpecificStaticMessage.hpp>

namespace DesignDocumentCreator
{

template<MessageName messageName>
SpecificStaticMessage<messageName> convertGenericToSpecificStatic(GenericMessage& genericMessage)
{
    SpecificStaticMessage<messageName> SpecificStaticMessage;
    typedef typename SpecificStaticMessage<messageName>::SackType SackType;
    SackType& payloadReference = SpecificStaticMessage.getPayloadReference();
    alba::AlbaMemoryBuffer& payloadBufferReference = genericMessage.getPayloadBufferReference();
    assert(sizeof(SackType) == genericMessage.getPayloadBufferReference().getSize());
    payloadReference = *reinterpret_cast<SackType*>(payloadBufferReference.getBufferPointer());
    SpecificStaticMessage.setSender(genericMessage.getSender());
    SpecificStaticMessage.setReceiver(genericMessage.getReceiver());
    return SpecificStaticMessage;
}

template<MessageName messageName>
GenericMessage convertSpecificToGeneric(SpecificStaticMessage<messageName>& SpecificStaticMessage)
{
    typedef typename SpecificStaticMessage<messageName>::SackType SackType;
    SackType& payloadReference = SpecificStaticMessage.getPayloadReference();
    GenericMessage genericMessage(SpecificStaticMessage.getMessageName(), &payloadReference, sizeof(SackType));
    genericMessage.setSender(SpecificStaticMessage.getSender());
    genericMessage.setReceiver(SpecificStaticMessage.getReceiver());
    return genericMessage;
}
}
