#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class MessageName
{
    Empty,
    SampleStaticMessage,
    SampleDynamicArrayMessage,
    SampleDynamicPolymorphicMessage
#define MESSAGE_NAME_MACRO(MESSAGE_NAME) ,MESSAGE_NAME
    #include <FeatureSpecificFiles/MessageNameMacro.hpp>
#undef MESSAGE_NAME_MACRO
};

}
