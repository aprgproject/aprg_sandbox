#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Events/OtherEventType.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Timers/TimerType.hpp>
#include <Common/Uml/UmlPositionType.hpp>

#include <string>

namespace DesignDocumentCreator
{

namespace StringHelpers
{
    std::string convertToString(ComponentName const componentName);
    std::string convertToString(MessageName const componentName);
    std::string convertToString(TimerType const timerType);
    std::string convertToString(UmlPositionType const position);
    std::string convertToString(OtherEventType const otherEventType);
    std::string convertToString(ComponentNames const componentNames);
    bool isTcomMessage(std::string const& messageName);
    bool isDspMessage(std::string const& messageName);
    bool isNbapMessage(std::string const& messageName);
}
}