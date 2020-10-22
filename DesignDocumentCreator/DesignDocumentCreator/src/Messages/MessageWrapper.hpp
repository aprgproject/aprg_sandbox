#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class MessageName;

template <MessageName messageName>
struct MessageWrapper
{
    static_assert((int)messageName!=0, "Message wrapper is used without sack");
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
