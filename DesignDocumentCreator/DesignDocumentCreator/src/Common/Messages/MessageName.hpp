#pragma once

#include <string>

namespace DesignDocumentCreator
{

enum class MessageName
{
    EMPTY,
    MESSAGE_SAMPLE
#include <FeatureSpecificFiles/MessageName.hpp>

};

}
