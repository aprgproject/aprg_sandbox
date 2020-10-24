#include "BtsLogTime.hpp"

#include <AlbaStringHelper.hpp>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

BtsLogTime::BtsLogTime()
    : m_years(0)
    , m_months(0)
    , m_days(0)
    , m_seconds(0)
    , m_microseconds(0)
{}

BtsLogTime::BtsLogTime(BtsLogTimeType logTimeType, string const& timeStampString)
    : m_years(0)
    , m_months(0)
    , m_days(0)
    , m_seconds(0)
    , m_microseconds(0)
{
    setTimeByTimeStamp(logTimeType, timeStampString);
}

void BtsLogTime::setTimeByTimeStamp(BtsLogTimeType logTimeType, string const& timeStampString)
{
    vector <int> timeValues;
    string timeValueString;

    for(char character: timeStampString)
    {
        if(stringHelper::isNumber(character))
        {
            timeValueString += character;
        }
        else if(!timeValueString.empty())
        {
            timeValues.push_back(stringHelper::convertStringToNumber<int>(timeValueString));
            timeValueString.clear();
        }
    }
    if(!timeValueString.empty())
    {
        timeValues.push_back(stringHelper::convertStringToNumber<int>(timeValueString));
    }

    if(BtsLogTimeType::PcTimeStamp == logTimeType)
    {
        if(6 == timeValues.size())
        {
            m_months = timeValues[1];
            m_days = timeValues[0];
            m_seconds = timeValues[2]*3600 + timeValues[3]*60 + timeValues[4];
            m_microseconds = timeValues[5]*1000;
        }
    }
    else
    {
        switch(timeValues.size())
        {
        case 6:
            m_months = timeValues[1];
            m_days = timeValues[0];
            m_seconds = timeValues[2]*3600 + timeValues[3]*60 + timeValues[4];
            m_microseconds = timeValues[5];
            break;
        case 7:
            m_years = timeValues[0];
            m_months = timeValues[1];
            m_days = timeValues[2];
            m_seconds = timeValues[3]*3600 + timeValues[4]*60 + timeValues[5];
            m_microseconds = timeValues[6];
            break;
        default:
            break;
        }
    }
}

bool BtsLogTime::isEmpty() const
{
    return (0 == m_years) && (0 == m_months) && (0 == m_days) && (0 == m_seconds) && (0 == m_microseconds);
}

bool BtsLogTime::isStartup() const
{
    return m_years<2010;
}

int BtsLogTime::getYears() const
{
    return m_years;
}

int BtsLogTime::getMonths() const
{
    return (int)m_months;
}

int BtsLogTime::getDays() const
{
    return m_days;
}

int BtsLogTime::getHours() const
{
    return m_seconds/3600;
}

int BtsLogTime::getMinutes() const
{
    return (m_seconds/60)%60;
}

int BtsLogTime::getSeconds() const
{
    return m_seconds%60;
}

int BtsLogTime::getTotalSeconds() const
{
    return m_seconds;
}

int BtsLogTime::getMicroSeconds() const
{
    return m_microseconds;
}

string BtsLogTime::getEquivalentString() const
{
    string separator("|");
    stringstream ss;
    ss << setw(4) << getYears() << separator;
    ss << setw(2) << getMonths() << separator;
    ss << setw(2) << getDays() << separator;
    ss << setw(2) << getHours() << separator;
    ss << setw(2) << getMinutes() << separator;
    ss << setw(2) << getSeconds() << separator;
    ss << setw(6) << getMicroSeconds();
    return ss.str();
}

string BtsLogTime::getEquivalentStringPcTimeFormat() const
{
    stringstream ss;
    ss << setw(2) << setfill('0') << getDays() << ".";
    ss << setw(2) << setfill('0') << getMonths() << " ";
    ss << setw(2) << setfill('0') << getHours() << ":";
    ss << setw(2) << setfill('0') << getMinutes() << ":";
    ss << setw(2) << setfill('0') << getSeconds() << ".";
    ss << setw(6) << setfill('0') << getMicroSeconds();
    return ss.str();
}

string BtsLogTime::getEquivalentStringBtsTimeFormat() const
{
    stringstream ss;
    ss << "<";
    ss << setfill('0') << setw(4) << getYears() << "-";
    ss << setfill('0') << setw(2) << getMonths() << "-";
    ss << setfill('0') << setw(2) << getDays() << "T";
    ss << setfill('0') << setw(2) << getHours() << ":";
    ss << setfill('0') << setw(2) << getMinutes() << ":";
    ss << setfill('0') << setw(2) << getSeconds() << ".";
    ss << setfill('0') << setw(6) << getMicroSeconds();
    ss << "Z>";

    return ss.str();
}

bool BtsLogTime::operator<(BtsLogTime const& btsLogTimeToCompare) const
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

bool BtsLogTime::operator>(BtsLogTime const& btsLogTimeToCompare) const
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

bool BtsLogTime::operator==(BtsLogTime const& btsLogTimeToCompare) const
{
    if(m_years != btsLogTimeToCompare.m_years) return false;
    if(m_months != btsLogTimeToCompare.m_months) return false;
    if(m_days != btsLogTimeToCompare.m_days) return false;
    if(m_seconds != btsLogTimeToCompare.m_seconds) return false;
    if(m_microseconds != btsLogTimeToCompare.m_microseconds) return false;
    return true;
}

BtsLogTime BtsLogTime::operator+(BtsLogTime const& btsLogTime2) const
{
    BtsLogTime btsLogTime1(*this);
    btsLogTime1.m_years += btsLogTime2.m_years;
    btsLogTime1.m_months += btsLogTime2.m_months;
    btsLogTime1.m_days += btsLogTime2.m_days;
    btsLogTime1.m_seconds += btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds += btsLogTime2.m_microseconds;
    btsLogTime1.reorganizeOverflowValues();
    return btsLogTime1;
}

BtsLogTime BtsLogTime::operator-(BtsLogTime const& btsLogTime2) const
{
    BtsLogTime btsLogTime1(*this);
    btsLogTime1.m_years -= btsLogTime2.m_years;
    btsLogTime1.m_months -= btsLogTime2.m_months;
    btsLogTime1.m_days -= btsLogTime2.m_days;
    btsLogTime1.m_seconds -= btsLogTime2.m_seconds;
    btsLogTime1.m_microseconds -= btsLogTime2.m_microseconds;
    btsLogTime1.reorganizeUnderflowValues();
    return btsLogTime1;
}

void BtsLogTime::reorganizeOverflowValues()
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

void BtsLogTime::reorganizeUnderflowValues()
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

ostream& operator<<(ostream & out, BtsLogTime const& btsLogTime)
{
    out << btsLogTime.m_years << endl;
    out << btsLogTime.m_months << endl;
    out << btsLogTime.m_days << endl;
    out << btsLogTime.m_seconds << endl;
    out << btsLogTime.m_microseconds;
    return out;
}

istream& operator>>(istream & in, BtsLogTime& btsLogTime)
{
    in >> btsLogTime.m_years;
    in >> btsLogTime.m_months;
    in >> btsLogTime.m_days;
    in >> btsLogTime.m_seconds;
    in >> btsLogTime.m_microseconds;
    return in;
}

}
