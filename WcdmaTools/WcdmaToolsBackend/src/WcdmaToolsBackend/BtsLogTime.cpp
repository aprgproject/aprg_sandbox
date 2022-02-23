#include "BtsLogTime.hpp"

#include <Common/File/AlbaFileParameterReader.hpp>
#include <Common/File/AlbaFileParameterWriter.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iomanip>
#include <sstream>
#include <vector>

using namespace alba;
using namespace std;

namespace wcdmaToolsBackend
{

BtsLogTime::BtsLogTime()
    : m_dateTime()
{}

BtsLogTime::BtsLogTime(BtsLogTimeType logTimeType, string const& timeStampString)
    : m_dateTime()
{
    setTimeByTimeStamp(logTimeType, timeStampString);
}

void BtsLogTime::clear()
{
    m_dateTime.clear();
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

unsigned int BtsLogTime::getYears() const
{
    return m_dateTime.getYears();
}

unsigned int BtsLogTime::getMonths() const
{
    return m_dateTime.getMonths();
}

unsigned int BtsLogTime::getDays() const
{
    return m_dateTime.getDays();
}

unsigned int BtsLogTime::getHours() const
{
    return m_dateTime.getHours();
}

unsigned int BtsLogTime::getMinutes() const
{
    return m_dateTime.getMinutes();
}

unsigned int BtsLogTime::getSeconds() const
{
    return m_dateTime.getSeconds();
}

unsigned int BtsLogTime::getTotalSeconds() const
{
    return m_dateTime.getTotalSecondsInHourMinutesSeconds();
}

unsigned int BtsLogTime::getMicroSeconds() const
{
    return m_dateTime.getMicroSeconds();
}

void BtsLogTime::clearMicroSeconds()
{
    m_dateTime.clearMicroSeconds();
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
    AlbaFileParameterWriter writer(out);
    writer.writeData<unsigned int>(btsLogTime.getYears());
    writer.writeData<unsigned int>(btsLogTime.getMonths());
    writer.writeData<unsigned int>(btsLogTime.getDays());
    writer.writeData<unsigned int>(btsLogTime.getHours());
    writer.writeData<unsigned int>(btsLogTime.getMinutes());
    writer.writeData<unsigned int>(btsLogTime.getSeconds());
    writer.writeData<unsigned int>(btsLogTime.getMicroSeconds());
    return out;
}

istream& operator>>(istream & in, BtsLogTime& btsLogTime)
{
    AlbaFileParameterReader reader(in);
    unsigned int years(reader.readData<unsigned int>());
    unsigned int months(reader.readData<unsigned int>());
    unsigned int days(reader.readData<unsigned int>());
    unsigned int hours(reader.readData<unsigned int>());
    unsigned int minutes(reader.readData<unsigned int>());
    unsigned int seconds(reader.readData<unsigned int>());
    unsigned int microseconds(reader.readData<unsigned int>());
    btsLogTime.m_dateTime.setTime((unsigned short int)years, (unsigned char)months, (unsigned char)days, (unsigned char)hours, (unsigned char)minutes, (unsigned char)seconds, microseconds);
    return in;
}

}
