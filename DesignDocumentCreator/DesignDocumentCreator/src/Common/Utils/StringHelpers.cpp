#include <AlbaStringHelper.hpp>
#include "StringHelpers.hpp"

using namespace alba;
using namespace DesignDocumentCreator::UmlConfiguration;
using namespace std;

namespace DesignDocumentCreator
{

#define GET_ENUM_STRING(en) \
    case en: \
    result = #en;\
    break;

std::string StringHelpers::convertToString(ComponentName const componentName)
{
    string result;
    switch(componentName)
    {
    GET_ENUM_STRING(ComponentName::EMPTY)
            GET_ENUM_STRING(ComponentName::SampleComponent)
        #include <FeatureSpecificFiles/ConvertToStringComponentName.hpp>
    }
    return stringHelper::getStringAfterThisString(result, "ComponentName::");
}

std::string StringHelpers::convertToString(MessageName const messageName)
{
    string result;
    switch(messageName)
    {
    GET_ENUM_STRING(MessageName::EMPTY)
            GET_ENUM_STRING(MessageName::MESSAGE_SAMPLE)
        #include <FeatureSpecificFiles/ConvertToStringMessageName.hpp>
    }
    return stringHelper::getStringAfterThisString(result, "MessageName::");
}

std::string StringHelpers::convertToString(TimerType const timerType)
{
    string result;
    switch(timerType)
    {
    GET_ENUM_STRING(TimerType::EMPTY)
            GET_ENUM_STRING(TimerType::CELL_TIMER)
            GET_ENUM_STRING(TimerType::DSP_TIMER)
            GET_ENUM_STRING(TimerType::CARRIER_RESOURCE_TIMER)
    }
    return stringHelper::getStringAfterThisString(result, "TimerType::");
}

std::string StringHelpers::convertToString(UmlLogParticipant const participant)
{
    string result;
    switch(participant)
    {
    GET_ENUM_STRING(UmlLogParticipant::actor)
            GET_ENUM_STRING(UmlLogParticipant::boundary)
            GET_ENUM_STRING(UmlLogParticipant::control)
            GET_ENUM_STRING(UmlLogParticipant::entity)
            GET_ENUM_STRING(UmlLogParticipant::database)
            GET_ENUM_STRING(UmlLogParticipant::participant)
    }
    return stringHelper::getStringAfterThisString(result, "UmlLogParticipant::");
}

std::string StringHelpers::convertToString(UmlLogPosition const position)
{
    string result;
    switch(position)
    {
    GET_ENUM_STRING(UmlLogPosition::right)
            GET_ENUM_STRING(UmlLogPosition::left)
            GET_ENUM_STRING(UmlLogPosition::over)
    }
    return stringHelper::getStringAfterThisString(result, "UmlLogPosition::");
}

bool StringHelpers::isTcomInternalMessage(string const& messageName)
{
    return stringHelper::isEqualWithLowestCommonLength(messageName, "TC_");
}

bool StringHelpers::isDspMessage(string const& messageName)
{
    return stringHelper::isEqualWithLowestCommonLength(messageName, "BB_");
}

bool StringHelpers::isNbapMessage(string const& messageName)
{
    return stringHelper::isEqualWithLowestCommonLength(messageName, "API_TCOM");
}

#undef GET_ENUM_STRING

}
