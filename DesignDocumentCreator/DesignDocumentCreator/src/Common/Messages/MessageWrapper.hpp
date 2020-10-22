#pragma once

#include <cassert>
#include <Common/Messages/MessageName.hpp>
#include <string>

namespace DesignDocumentCreator
{

template <MessageName messageName>
struct MessageWrapper
{
    static_assert(true, "Message wrapper is used without sack");
};

#define WRAP_MESSAGE(messageName, sack)                                     \
    template <>                                                             \
    struct MessageWrapper<messageName>                                      \
    {                                                                       \
        typedef sack SackType;                                              \
        static MessageName getMessageName(){return messageName;}            \
        static std::string getString(){return #messageName;}                \
    };

}
