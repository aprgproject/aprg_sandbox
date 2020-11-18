#include "AlbaDateTimeFormat.hpp"

using namespace std;

namespace alba
{

AlbaDateTimeFormat::AlbaDateTimeFormat()
    : m_years(0)
    , m_months(0)
    , m_days(0)
    , m_seconds(0)
    , m_microseconds(0)
    , m_isEmpty(false)
{}

AlbaDateTimeFormat::AlbaDateTimeFormat(unsigned int years, unsigned int months, unsigned int days, unsigned int seconds, unsigned int microseconds)
    : m_years((int)years)
    , m_months((int)months)
    , m_days((int)days)
    , m_seconds((int)seconds)
    , m_microseconds((int)microseconds)
    , m_isEmpty(true)
{}

void AlbaDateTimeFormat::setTime(unsigned int years, unsigned int months, unsigned int days, unsigned int seconds, unsigned int microseconds)
{
    m_years = (int)years;
    m_months = (int)months;
    m_days = (int)days;
    m_seconds = (int)seconds;
    m_microseconds = (int)microseconds;
    m_isEmpty = true;
}

bool AlbaDateTimeFormat::isEmpty() const
{
    return m_isEmpty;
}

int AlbaDateTimeFormat::getYears() const
{
    return m_years;
}

int AlbaDateTimeFormat::getMonths() const
{
    return (int)m_months;
}

int AlbaDateTimeFormat::getDays() const
{
    return m_days;
}

int AlbaDateTimeFormat::getHours() const
{
    return m_seconds/3600;
}

int AlbaDateTimeFormat::getMinutes() const
{
    return (m_seconds/60)%60;
}

int AlbaDateTimeFormat::getSeconds() const
{
    return m_seconds%60;
}

int AlbaDateTimeFormat::getTotalSeconds() const
{
    return m_seconds;
}

int AlbaDateTimeFormat::getMicroSeconds() const
{
    return m_microseconds;
}

string AlbaDateTimeFormat::getPrintableString() const
{
    stringstream ss;
    ss << setw(4) << getYears() << "-";
    ss << setw(2) << getMonths() << "-";
    ss << setw(2) << getDays() << " ";
    ss << setw(2) << getHours() << "::";
    ss << setw(2) << getMinutes() << "::";
    ss << setw(2) << getSeconds() << "::";
    ss << setw(6) << getMicroSeconds();
    return ss.str();
}

bool AlbaDateTimeFormat::operator<(AlbaDateTimeFormat const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return true;
    if(m_years > btsLogTimeToCompare.m_years) return false;
    if(m_months < btsLogTimeToCompare.m_months) return true;
    if(m_months > btsLogTimeToCompare.m_months) return false;
    if(m_days < btsLogTimeToCompare.m_days) return true;
    if(m_days > btsLogTimeToCompare.m_days) return false;
    if(m_seconds < btsLogTimeToCompare.m_seconds) return true;
    if(m_seconds > btsLogTimeToCompare.m_seconds) return false;
    if(m_microseconds < btsLogTimeToCompare.m_microseconds) return true;
    if(m_microseconds > btsLogTimeToCompare.m_microseconds) return false;
    return false;
}

bool AlbaDateTimeFormat::operator>(AlbaDateTimeFormat const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return false;
    if(m_years > btsLogTimeToCompare.m_years) return true;
    if(m_months < btsLogTimeToCompare.m_months) return false;
    if(m_months > btsLogTimeToCompare.m_months) return true;
    if(m_days < btsLogTimeToCompare.m_days) return false;
    if(m_days > btsLogTimeToCompare.m_days) return true;
    if(m_seconds < btsLogTimeToCompare.m_seconds) return false;
    if(m_seconds > btsLogTimeToCompare.m_seconds) return true;
    if(m_microseconds < btsLogTimeToCompare.m_microseconds) return false;
    if(m_microseconds > btsLogTimeToCompare.m_microseconds) return true;
    return false;

}

bool AlbaDateTimeFormat::operator==(AlbaDateTimeFormat const& btsLogTimeToCompare) const
{
    if(m_years != btsLogTimeToCompare.m_years) return false;
    if(m_months != btsLogTimeToCompare.m_months) return false;
    if(m_days != btsLogTimeToCompare.m_days) return false;
    if(m_seconds != btsLogTimeToCompare.m_seconds) return false;
    if(m_microseconds != btsLogTimeToCompare.m_microseconds) return false;
    return true;
}

bool AlbaDateTimeFormat::operator!=(AlbaDateTimeFormat const& btsLogTimeToCompare) const
{
    !((*this)==btsLogTimeToCompare);
}

AlbaDateTimeFormat AlbaDateTimeFormat::operator+(AlbaDateTimeFormat const& btsLogTime2) const
{
    AlbaDateTimeFormat btsLogTime1(*this);
    btsLogTime1.m_years += btsLogTime2.m_years;
    btsLogTime1.m_months += btsLogTime2.m_months;
    btsLogTime1.m_days += btsLogTime2.m_days;
    btsLogTime1.m_seconds += btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds += btsLogTime2.m_microseconds;
    btsLogTime1.m_isEmpty = true;
    btsLogTime1.reorganizeOverflowValues();
    return btsLogTime1;
}

AlbaDateTimeFormat AlbaDateTimeFormat::operator-(AlbaDateTimeFormat const& btsLogTime2) const
{
    AlbaDateTimeFormat btsLogTime1(*this);
    btsLogTime1.m_years -= btsLogTime2.m_years;
    btsLogTime1.m_months -= btsLogTime2.m_months;
    btsLogTime1.m_days -= btsLogTime2.m_days;
    btsLogTime1.m_seconds -= btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds -= btsLogTime2.m_microseconds;
    btsLogTime1.m_isEmpty = true;
    btsLogTime1.reorganizeUnderflowValues();
    return btsLogTime1;
}

void AlbaDateTimeFormat::reorganizeOverflowValues()
{
    while(m_microseconds >= 1000000)
    {
        m_seconds++;
        m_microseconds -= 1000000;
    }

    while(m_seconds >= 86400)
    {
        m_days++;
        m_seconds -= 86400;
    }
}

void AlbaDateTimeFormat::reorganizeUnderflowValues()
{
    while(m_microseconds < 0)
    {
        m_seconds--;
        m_microseconds += 1000000;
    }

    while(m_seconds < 0)
    {
        m_days--;
        m_seconds += 86400;
    }
}

}//namespace alba
