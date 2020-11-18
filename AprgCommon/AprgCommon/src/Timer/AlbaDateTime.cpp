#include "AlbaDateTime.hpp"

#include <String/AlbaStringHelper.hpp>

#include <iomanip>
#include <sstream>

using namespace std;

namespace alba
{

AlbaDateTime::AlbaDateTime()
    : m_years(0)
    , m_months(0)
    , m_days(0)
    //, m_hours(0)
    //, m_minutes(0)
    //, m_seconds(0)
    //, m_microseconds(0)
    //, m_isEmpty(false)
{}

AlbaDateTime::AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
    : m_years(years)
    , m_months(months)
    , m_days(days)
    //, m_hours(hours)
    //, m_minutes(minutes)
    //, m_seconds(seconds)
    //, m_microseconds(microseconds)
    //, m_isEmpty(true)
{}

void AlbaDateTime::setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
{
    m_years = years;
    m_months = months;
    m_days = days;
    //m_hours = hours;
    //m_minutes = minutes;
    //m_seconds = seconds;
    //m_microseconds = microseconds;
    //m_isEmpty = true;
}

bool AlbaDateTime::isEmpty() const
{
    //return m_isEmpty;
}

int AlbaDateTime::getYears() const
{
    return m_years;
}

int AlbaDateTime::getMonths() const
{
    return (int)m_months;
}

int AlbaDateTime::getDays() const
{
    return m_days;
}

int AlbaDateTime::getHours() const
{
    //return m_seconds/3600;
}

int AlbaDateTime::getMinutes() const
{
    //return (m_seconds/60)%60;
}

int AlbaDateTime::getSeconds() const
{
    //return m_seconds%60;
}

int AlbaDateTime::getTotalSeconds() const
{
    //return m_seconds;
}

int AlbaDateTime::getMicroSeconds() const
{
    //return m_microseconds;
}

string AlbaDateTime::getPrintableString() const
{
    stringstream ss;
    ss << setfill('0');
    ss << setw(4) << getYears() << "-";
    ss << setw(2) << getMonths() << "-";
    ss << setw(2) << getDays() << " ";
    ss << setw(2) << getHours() << "::";
    ss << setw(2) << getMinutes() << "::";
    ss << setw(2) << getSeconds() << ".";
    ss << setw(6) << getMicroSeconds();
    return ss.str();
}

bool AlbaDateTime::operator<(AlbaDateTime const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return true;
    if(m_years > btsLogTimeToCompare.m_years) return false;
    if(m_months < btsLogTimeToCompare.m_months) return true;
    if(m_months > btsLogTimeToCompare.m_months) return false;
    if(m_days < btsLogTimeToCompare.m_days) return true;
    if(m_days > btsLogTimeToCompare.m_days) return false;
    //if(m_seconds < btsLogTimeToCompare.m_seconds) return true;
    //if(m_seconds > btsLogTimeToCompare.m_seconds) return false;
    //if(m_microseconds < btsLogTimeToCompare.m_microseconds) return true;
    //if(m_microseconds > btsLogTimeToCompare.m_microseconds) return false;
    return false;
}

bool AlbaDateTime::operator>(AlbaDateTime const& btsLogTimeToCompare) const
{
    if(m_years < btsLogTimeToCompare.m_years) return false;
    if(m_years > btsLogTimeToCompare.m_years) return true;
    if(m_months < btsLogTimeToCompare.m_months) return false;
    if(m_months > btsLogTimeToCompare.m_months) return true;
    if(m_days < btsLogTimeToCompare.m_days) return false;
    if(m_days > btsLogTimeToCompare.m_days) return true;
    //if(m_seconds < btsLogTimeToCompare.m_seconds) return false;
    //if(m_seconds > btsLogTimeToCompare.m_seconds) return true;
    //if(m_microseconds < btsLogTimeToCompare.m_microseconds) return false;
    //if(m_microseconds > btsLogTimeToCompare.m_microseconds) return true;
    return false;

}

bool AlbaDateTime::operator==(AlbaDateTime const& btsLogTimeToCompare) const
{
    if(m_years != btsLogTimeToCompare.m_years) return false;
    if(m_months != btsLogTimeToCompare.m_months) return false;
    if(m_days != btsLogTimeToCompare.m_days) return false;
    //if(m_seconds != btsLogTimeToCompare.m_seconds) return false;
    //if(m_microseconds != btsLogTimeToCompare.m_microseconds) return false;
    return true;
}

bool AlbaDateTime::operator!=(AlbaDateTime const& btsLogTimeToCompare) const
{
    return !((*this)==btsLogTimeToCompare);
}

AlbaDateTime AlbaDateTime::operator+(AlbaDateTime const& btsLogTime2) const
{
    AlbaDateTime btsLogTime1(*this);
    btsLogTime1.m_years += btsLogTime2.m_years;
    btsLogTime1.m_months += btsLogTime2.m_months;
    btsLogTime1.m_days += btsLogTime2.m_days;
    //btsLogTime1.m_seconds += btsLogTime2.m_seconds;
    //btsLogTime1.m_microseconds += btsLogTime2.m_microseconds;
    //btsLogTime1.m_isEmpty = true;
    //btsLogTime1.reorganizeOverflowValues();
    return btsLogTime1;
}

AlbaDateTime AlbaDateTime::operator-(AlbaDateTime const& btsLogTime2) const
{
    AlbaDateTime btsLogTime1(*this);
    btsLogTime1.m_years -= btsLogTime2.m_years;
    btsLogTime1.m_months -= btsLogTime2.m_months;
    btsLogTime1.m_days -= btsLogTime2.m_days;
    //btsLogTime1.m_seconds -= btsLogTime2.m_seconds;
    //btsLogTime1.m_microseconds -= btsLogTime2.m_microseconds;
    //btsLogTime1.m_isEmpty = true;
    //btsLogTime1.reorganizeUnderflowValues();
    return btsLogTime1;
}

void AlbaDateTime::reorganizeOverflowValues()
{
    /*while(m_microseconds >= 1000000)
    {
        m_seconds++;
        m_microseconds -= 1000000;
    }

    while(m_seconds >= 86400)
    {
        m_days++;
        m_seconds -= 86400;
    }*/
}

void AlbaDateTime::reorganizeUnderflowValues()
{
    /*while(m_microseconds < 0)
    {
        m_seconds--;
        m_microseconds += 1000000;
    }

    while(m_seconds < 0)
    {
        m_days--;
        m_seconds += 86400;
    }*/
}

}//namespace alba
