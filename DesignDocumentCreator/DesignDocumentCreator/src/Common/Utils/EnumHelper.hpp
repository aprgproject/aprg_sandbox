#pragma once

#include <Components/ComponentName.hpp>
#include <Messages/MessageName.hpp>
#include <Timers/TimerType.hpp>

namespace DesignDocumentCreator
{

namespace EnumHelper
{
    std::string convertToString(ComponentName const componentName);
    std::string convertToString(MessageName const componentName);
    std::string convertToString(TimerType const timerType);
}

}
