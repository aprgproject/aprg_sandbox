#pragma once

#include <Common/Components/ComponentName.hpp>
#include <Common/Messages/MessageName.hpp>
#include <Common/Timers/TimerType.hpp>
#include <Common/Uml/UmlLogParticipant.hpp>
#include <Common/Uml/UmlLogPosition.hpp>

#include <string>

namespace DesignDocumentCreator
{

namespace StringHelpers
{
    std::string convertToString(ComponentName const componentName);
    std::string convertToString(MessageName const componentName);
    std::string convertToString(TimerType const timerType);
    std::string convertToString(UmlLogParticipant const participant);
    std::string convertToString(UmlLogPosition const position);
    bool isTcomInternalMessage(std::string const& messageName);
    bool isDspMessage(std::string const& messageName);
    bool isNbapMessage(std::string const& messageName);
}

}
