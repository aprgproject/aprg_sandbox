#pragma once

#include <Common/Messages/GenericMessage.hpp>
#include <Common/Messages/SpecificStaticMessage.hpp>
#include <Common/Messages/SpecificDynamicArrayMessage.hpp>
#include <Common/Messages/SpecificDynamicPolymorphicMessage.hpp>

namespace DesignDocumentCreator
{
template<MessageName messageName>
SpecificStaticMessage<messageName> convertGenericToSpecificStatic(GenericMessage& genericMessage)
{
    return SpecificStaticMessage<messageName> (genericMessage.getPayloadBufferConstReference(), genericMessage.getSender(), genericMessage.getReceiver());
}

template<MessageName messageName, unsigned int dynamicPayloadItemSize>
SpecificDynamicArrayMessage<messageName, dynamicPayloadItemSize> convertGenericToSpecificDynamicArray(GenericMessage& genericMessage)
{
    return SpecificDynamicArrayMessage<messageName, dynamicPayloadItemSize>(genericMessage.getPayloadBufferConstReference(), genericMessage.getSender(), genericMessage.getReceiver());
}

template<MessageName messageName, typename DynamicPartSackType>
SpecificDynamicPolymorphicMessage<messageName, DynamicPartSackType> convertGenericToSpecificDynamicPolymorphic(GenericMessage& genericMessage)
{
    return SpecificDynamicPolymorphicMessage<messageName, DynamicPartSackType>(genericMessage.getPayloadBufferConstReference(), genericMessage.getSender(), genericMessage.getReceiver());
}

template<MessageName messageName>
GenericMessage convertSpecificStaticToGeneric(SpecificStaticMessage<messageName>& specificStaticMessage)
{
    return GenericMessage(specificStaticMessage.getMessageName(), specificStaticMessage.createBuffer(), specificStaticMessage.getSender(), specificStaticMessage.getReceiver());
}

template<MessageName messageName, unsigned int dynamicPayloadItemSize>
GenericMessage convertSpecificDynamicArrayToGeneric(SpecificDynamicArrayMessage<messageName, dynamicPayloadItemSize>& specificDynamicArrayMessage)
{
    return GenericMessage(specificDynamicArrayMessage.getMessageName(), specificDynamicArrayMessage.createBuffer(), specificDynamicArrayMessage.getSender(), specificDynamicArrayMessage.getReceiver());
}

template<MessageName messageName, typename DynamicPartSackType>
GenericMessage convertSpecificDynamicPolymorphicToGeneric(SpecificDynamicPolymorphicMessage<messageName, DynamicPartSackType>& specificDynamicPolymorphicMessage)
{
    return GenericMessage(specificDynamicPolymorphicMessage.getMessageName(), specificDynamicPolymorphicMessage.createBuffer(), specificDynamicPolymorphicMessage.getSender(), specificDynamicPolymorphicMessage.getReceiver());
}

}