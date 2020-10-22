#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Timers/TimerType.hpp>

namespace DesignDocumentCreator
{
namespace EnumHelper
{
    std::string convertToString(ComponentName const componentName);    std::string convertToString(MessageName const componentName);
    std::string convertToString(TimerType const timerType);
}

}
