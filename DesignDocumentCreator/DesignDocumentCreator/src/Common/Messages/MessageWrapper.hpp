#pragma once

#include <Common/Messages/MessageName.hpp>

#include <cassert>
#include <string>

namespace DesignDocumentCreator
{

template <MessageName messageName>
struct MessageWrapper
{
    static_assert(true, "Message wrapper is used without sack");
};

#define WRAP_STATIC_MESSAGE(messageName, sack)                              \
    template <>                                                             \
    struct MessageWrapper<messageName>                                      \
    {                                                                       \
        typedef sack SackType;                                              \
        static MessageName getMessageName(){return messageName;}            \
        static std::string getString(){return #messageName;}                \
    };

#define WRAP_DYNAMIC_ARRAY_MESSAGE(messageName, staticPartSack, dynamicPartSack)    \
    template <>                                                                     \
    struct MessageWrapper<messageName>                                              \
    {                                                                                \
        typedef staticPartSack StaticPartSackType;                                  \
        typedef dynamicPartSack DynamicPartSackType;                           \
        static MessageName getMessageName(){return messageName;}            \
        static std::string getString(){return #messageName;}                \
    };

#define WRAP_DYNAMIC_POLYMORPHIC_MESSAGE(messageName, staticPartSack, dynamicPlaceHolderSack)    \
    template <>                                                                                  \
    struct MessageWrapper<messageName>                                                           \
    {                                                                                            \
        typedef staticPartSack StaticPartSackType;                                                   \
        typedef dynamicPlaceHolderSack DynamicPlaceHolderSackType;                               \
        static MessageName getMessageName(){return messageName;}                                 \
        static std::string getString(){return #messageName;}                                     \
    };

}
