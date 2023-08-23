#pragma once

#include <Common/Messages/MessageName.hpp>

#include <cassert>
#include <string>

namespace DesignDocumentCreator {

template <MessageName messageName>
struct MessageWrapper {
    static_assert(true, "Message wrapper is used without sack");
};

#define WRAP_STATIC_MESSAGE(messageName, sack)                      \
    template <>                                                     \
    struct MessageWrapper<messageName> {                            \
        typedef sack MessageStaticSackType;                         \
        static MessageName getMessageName() { return messageName; } \
        static std::string getString() { return #messageName; }     \
    };

#define WRAP_DYNAMIC_ARRAY_MESSAGE(messageName, sack, dynamicPartSack) \
    template <>                                                        \
    struct MessageWrapper<messageName> {                               \
        typedef sack MessageDynamicArraySackType;                      \
        typedef dynamicPartSack DynamicPartSackType;                   \
        static MessageName getMessageName() { return messageName; }    \
        static std::string getString() { return #messageName; }        \
    };

#define WRAP_DYNAMIC_POLYMORPHIC_MESSAGE(messageName, sack, dynamicPlaceHolderSack) \
    template <>                                                                     \
    struct MessageWrapper<messageName> {                                            \
        typedef sack MessageDynamicPolymorphicSackType;                             \
        typedef dynamicPlaceHolderSack DynamicPlaceHolderSackType;                  \
        static MessageName getMessageName() { return messageName; }                 \
        static std::string getString() { return #messageName; }                     \
    };

}  // namespace DesignDocumentCreator
