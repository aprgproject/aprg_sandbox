#include <Common/Timers/Timers.hpp>

namespace DesignDocumentCreator
{

Timer::Timer()
    : m_timerType(TimerType::EMPTY)
    , m_timerId(0)
{}

Timer::Timer(TimerType const timerType, TimerId const timerId)
    : m_timerType(timerType)
    , m_timerId(timerId)
{}

TimerType Timer::getType() const
{
    return m_timerType;
}

TimerId Timer::getId() const
{
    return m_timerId;
}

}
