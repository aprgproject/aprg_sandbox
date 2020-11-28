#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class MessageName
{
    EMPTY,
    MESSAGE_SAMPLE
#define MESSAGE_NAME_MACRO(MESSAGE_NAME) ,MESSAGE_NAME
    #include <FeatureSpecificFiles/MessageNameMacro.hpp>
#undef MESSAGE_NAME_MACRO

};
}