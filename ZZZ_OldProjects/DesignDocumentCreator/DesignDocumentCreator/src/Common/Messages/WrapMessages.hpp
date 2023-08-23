#pragma once

#include <Common/Messages/MessageWrapper.hpp>
#include <Common/Sacks/Sacks.hpp>

namespace DesignDocumentCreator {

WRAP_STATIC_MESSAGE(MessageName::SampleStaticMessage, StaticMessageSack)
WRAP_DYNAMIC_ARRAY_MESSAGE(MessageName::SampleDynamicArrayMessage, DynamicArrayMessageSack, DynamicArrayPartSack)
WRAP_DYNAMIC_POLYMORPHIC_MESSAGE(
    MessageName::SampleDynamicPolymorphicMessage, DynamicPolymorphicMessageSack, DynamicPlaceHolderSack)

}  // namespace DesignDocumentCreator
