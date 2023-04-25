#pragma once

#include <Common/Timers/TimerType.hpp>

namespace DesignDocumentCreator {

typedef unsigned int TimerId;

class Timer {
public:
    Timer();
    Timer(TimerType const timerType, TimerId const timerId);
    TimerType getType() const;
    TimerId getId() const;

private:
    TimerType m_timerType;
    TimerId m_timerId;
};

}  // namespace DesignDocumentCreator
