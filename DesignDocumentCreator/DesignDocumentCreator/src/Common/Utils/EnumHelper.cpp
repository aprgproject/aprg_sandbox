#include "EnumHelper.hpp"

namespace DesignDocumentCreator
{

#define GET_ENUM_STRING(en) \
    case en: \
    return #en;

std::string EnumHelper::convertToString(ComponentName const componentName)
{
    switch(componentName)
    {
    GET_ENUM_STRING(ComponentName::EMPTY)
            GET_ENUM_STRING(ComponentName::SampleComponent)
        #include <FeatureSpecificFiles/ConvertToStringComponentName.hpp>
    }
    return "";
}
std::string EnumHelper::convertToString(MessageName const messageName)
{
    switch(messageName)
    {
    GET_ENUM_STRING(MessageName::EMPTY)
            GET_ENUM_STRING(MessageName::MESSAGE_SAMPLE)
        #include <FeatureSpecificFiles/ConvertToStringMessageName.hpp>
    }
    return "";
}
std::string EnumHelper::convertToString(TimerType const timerType)
{
    switch(timerType)    {
    GET_ENUM_STRING(TimerType::EMPTY)
            GET_ENUM_STRING(TimerType::CELL_TIMER)
            GET_ENUM_STRING(TimerType::DSP_TIMER)
            GET_ENUM_STRING(TimerType::CARRIER_RESOURCE_TIMER)
    }
    return "";
}

#undef GET_ENUM_STRING

}
