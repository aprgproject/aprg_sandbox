#include "AlbaLocalTimer.hpp"

#include <Common/Time/AlbaLocalTimeHelper.hpp>

using namespace std;
using namespace std::chrono;

namespace alba
{

AlbaLocalTimer::AlbaLocalTimer()
    : m_time1(getSteadyTimeNow())
    , m_time2(m_time1)
{}

void AlbaLocalTimer::resetTimer()
{
    m_time1 = getSteadyTimeNow();
    m_time2 = m_time1;
}

void AlbaLocalTimer::stopTimer()
{
    m_time2 = getSteadyTimeNow();
}

unsigned int AlbaLocalTimer::getElapsedTimeInNanoseconds() const
{
    return duration_cast<std::chrono::nanoseconds>(m_time2-m_time1).count();
}

unsigned int AlbaLocalTimer::getElapsedTimeInMicroseconds() const
{
    return duration_cast<std::chrono::microseconds>(m_time2-m_time1).count();
}

unsigned int AlbaLocalTimer::getElapsedTimeInMilliseconds() const
{
    return duration_cast<std::chrono::milliseconds>(m_time2-m_time1).count();
}

unsigned int AlbaLocalTimer::getElapsedTimeInSeconds() const
{
    return duration_cast<std::chrono::seconds>(m_time2-m_time1).count();
}

unsigned int AlbaLocalTimer::getElapsedTimeInMinutes() const
{
    return duration_cast<std::chrono::minutes>(m_time2-m_time1).count();
}

unsigned int AlbaLocalTimer::getElapsedTimeInHours() const
{
    return duration_cast<std::chrono::hours>(m_time2-m_time1).count();
}

AlbaDateTime AlbaLocalTimer::getDifferenceAsAlbaDateTime() const
{
    AlbaDateTime result(0, 0, 0, 0, 0, 0, getElapsedTimeInMicroseconds()); // might overflow
    result.reorganizeValues();
    return result;
}

string AlbaLocalTimer::getElapsedTimeDisplayableString() const
{
    return getDifferenceAsAlbaDateTime().getPrintableStringFormat3();
}

}//namespace alba