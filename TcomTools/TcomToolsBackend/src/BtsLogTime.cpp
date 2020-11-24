#include "BtsLogTime.hpp"

#include <String/AlbaStringHelper.hpp>

#include <iomanip>
#include <sstream>
#include <vector>

using namespace alba;
using namespace std;

namespace tcomToolsBackend
{

BtsLogTime::BtsLogTime()
    : m_dateTime()
{}

BtsLogTime::BtsLogTime(BtsLogTimeType logTimeType, string const& timeStampString)
    : m_dateTime()
{
    setTimeByTimeStamp(logTimeType, timeStampString);
}

void BtsLogTime::setTimeByTimeStamp(BtsLogTimeType logTimeType, string const& timeStampString)
{
    unsigned int years=0;
    unsigned int months=0;
    unsigned int days=0;
    unsigned int hours=0;
    unsigned int minutes=0;
    unsigned int seconds=0;
    unsigned int microseconds=0;
    vector <unsigned int> timeValues;
    string timeValueString;

    for(char character: timeStampString)
    {
        if(stringHelper::isNumber(character))
        {
            timeValueString += character;
        }
        else if(!timeValueString.empty())
        {
            timeValues.push_back(stringHelper::convertStringToNumber<unsigned int>(timeValueString));
            timeValueString.clear();
        }
    }
    if(!timeValueString.empty())
    {
        timeValues.push_back(stringHelper::convertStringToNumber<unsigned int>(timeValueString));
    }

    if(BtsLogTimeType::PcTimeStamp == logTimeType)
    {
        if(6 == timeValues.size())
        {
            months = timeValues[1];
            days = timeValues[0];
            hours = timeValues[2];
            minutes = timeValues[3];
            seconds = timeValues[4];
            microseconds = timeValues[5]*1000;
        }
    }
    else
    {
        switch(timeValues.size())
        {
        case 6:
            months = timeValues[1];
            days = timeValues[0];
            hours = timeValues[2];
            minutes = timeValues[3];
            seconds = timeValues[4];
            microseconds = timeValues[5];
            break;
        case 7:
            years = timeValues[0];
            months = timeValues[1];
            days = timeValues[2];
            hours = timeValues[3];
            minutes = timeValues[4];
            seconds = timeValues[5];
            microseconds = timeValues[6];
            break;
        default:
            break;
        }
    }
    m_dateTime.setTime((unsigned short int)years, (unsigned char)months, (unsigned char)days, (unsigned char)hours, (unsigned char)minutes, (unsigned char)seconds, microseconds);
}

bool BtsLogTime::isEmpty() const
{
    return m_dateTime.isEmpty();
}

bool BtsLogTime::isStartup() const
{
    return m_dateTime.getYears()<2010;
}

int BtsLogTime::getYears() const
{
    return m_dateTime.getYears();
}

int BtsLogTime::getMonths() const
{
    return m_dateTime.getMonths();
}

int BtsLogTime::getDays() const
{
    return m_dateTime.getDays();
}

int BtsLogTime::getHours() const
{
    return m_dateTime.getHours();
}

int BtsLogTime::getMinutes() const
{
    return m_dateTime.getMinutes();
}

int BtsLogTime::getSeconds() const
{
    return m_dateTime.getSeconds();
}

int BtsLogTime::getTotalSeconds() const
{
    return m_dateTime.getTotalSecondsInHourMinutesSeconds();
}

int BtsLogTime::getMicroSeconds() const
{
    return m_dateTime.getMicroSeconds();
}

string BtsLogTime::getPrintableString() const
{
    return m_dateTime.getPrintableStringFormat1();
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
    return m_dateTime < btsLogTimeToCompare.m_dateTime;
}

bool BtsLogTime::operator>(BtsLogTime const& btsLogTimeToCompare) const
{
    return m_dateTime > btsLogTimeToCompare.m_dateTime;
}

bool BtsLogTime::operator==(BtsLogTime const& btsLogTimeToCompare) const
{
    return m_dateTime == btsLogTimeToCompare.m_dateTime;
}

BtsLogTime BtsLogTime::operator+(BtsLogTime const& btsLogTime2) const
{
    BtsLogTime result;
    BtsLogTime const& btsLogTime1(*this);
    result.m_dateTime = btsLogTime1.m_dateTime + btsLogTime2.m_dateTime;
    return result;
}

BtsLogTime BtsLogTime::operator-(BtsLogTime const& btsLogTime2) const
{
    BtsLogTime result;
    BtsLogTime const& btsLogTime1(*this);
    result.m_dateTime = btsLogTime1.m_dateTime - btsLogTime2.m_dateTime;
    return result;
}

ostream& operator<<(ostream & out, BtsLogTime const& btsLogTime)
{
    out << btsLogTime.getYears() << endl;
    out << btsLogTime.getMonths() << endl;
    out << btsLogTime.getDays() << endl;
    out << btsLogTime.getHours() << endl;
    out << btsLogTime.getMinutes() << endl;
    out << btsLogTime.getSeconds() << endl;
    out << btsLogTime.getMicroSeconds();
    return out;
}

istream& operator>>(istream & in, BtsLogTime& btsLogTime)
{
    unsigned int years=0;
    unsigned int months=0;
    unsigned int days=0;
    unsigned int hours=0;
    unsigned int minutes=0;
    unsigned int seconds=0;
    unsigned int microseconds=0;
    in >> years;
    in >> months;
    in >> days;
    in >> hours;
    in >> minutes;
    in >> seconds;
    in >> microseconds;
    btsLogTime.m_dateTime.setTime((unsigned short int)years, (unsigned char)months, (unsigned char)days, (unsigned char)hours, (unsigned char)minutes, (unsigned char)seconds, microseconds);
    return in;
}

}
