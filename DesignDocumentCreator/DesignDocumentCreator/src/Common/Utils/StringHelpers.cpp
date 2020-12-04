#include "StringHelpers.hpp"

#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba;
using namespace std;

namespace DesignDocumentCreator
{

#define GET_ENUM_STRING(en) case en: result = #en; break;

string StringHelpers::convertToString(ComponentName const componentName)
{
    string result;
    switch(componentName)
    {
#define COMPONENT_NAME_MACRO(COMPONENT_NAME) case ComponentName:: COMPONENT_NAME : result = #COMPONENT_NAME; break;
    COMPONENT_NAME_MACRO(Empty)
    COMPONENT_NAME_MACRO(SampleComponent)
    #include <FeatureSpecificFiles/ComponentNameMacro.hpp>
#undef COMPONENT_NAME_MACRO
    }
    return result;
}

string StringHelpers::convertToString(MessageName const messageName)
{
    string result;
    switch(messageName)
    {
#define MESSAGE_NAME_MACRO(MESSAGE_NAME) case MessageName:: MESSAGE_NAME : result = #MESSAGE_NAME; break;
    MESSAGE_NAME_MACRO(Empty)
    MESSAGE_NAME_MACRO(SampleStaticMessage)
    MESSAGE_NAME_MACRO(SampleDynamicArrayMessage)
    MESSAGE_NAME_MACRO(SampleDynamicPolymorphicMessage)
    #include <FeatureSpecificFiles/MessageNameMacro.hpp>
#undef MESSAGE_NAME_MACRO
    }
    return result;
}

string StringHelpers::convertToString(TimerType const timerType)
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

string StringHelpers::convertToString(OtherEventType const otherEventType)
{
    string result;
    switch(otherEventType)
    {
    GET_ENUM_STRING(OtherEventType::Empty)
            GET_ENUM_STRING(OtherEventType::MainProcessStartup)
            GET_ENUM_STRING(OtherEventType::SubProcessStartup)
    }
    return stringHelper::getStringAfterThisString(result, "OtherEventType::");
}

string StringHelpers::convertToString(UmlPositionType const position)
{
    string result;
    switch(position)
    {
    GET_ENUM_STRING(UmlPositionType::right)
            GET_ENUM_STRING(UmlPositionType::left)
            GET_ENUM_STRING(UmlPositionType::over)
    }
    return stringHelper::getStringAfterThisString(result, "UmlLogPosition::");
}

string StringHelpers::convertToString(ComponentNames const componentNames)
{
    string result(accumulate(componentNames.cbegin(), componentNames.cend(), string(""), [](string const& partialResult, ComponentName const componentName)
    {
        return partialResult+convertToString(componentName)+",";
    }));
    result = stringHelper::getStringWithoutCharAtTheEnd(result, ',');
    return result;
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
