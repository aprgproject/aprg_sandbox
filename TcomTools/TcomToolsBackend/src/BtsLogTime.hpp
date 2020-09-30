#pragma once

#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

namespace tcomToolsBackend
{

enum class BtsLogTimeType
{
    BtsTimeStamp,
    PcTimeStamp
};

class BtsLogTime
{
public:
    BtsLogTime();
    BtsLogTime(BtsLogTimeType logTimeType, string const& timeStampString);
    void setTimeByTimeStamp(BtsLogTimeType logTimeType, string const& timeStampString);
    bool isEmpty() const;
    bool isStartup() const;
    int getYears() const;
    int getMonths() const;
    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    int getTotalSeconds() const;
    int getMicroSeconds() const;
    string getEquivalentString() const;
    string getEquivalentStringPcTimeFormat() const;
    bool operator<(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator>(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator==(BtsLogTime const& btsLogTimeToCompare) const;
    BtsLogTime operator+(BtsLogTime const& btsLogTime) const;
    BtsLogTime operator-(BtsLogTime const& btsLogTime) const;
    friend ostream& operator<<(ostream & out, BtsLogTime const& btsLogTime);
    friend istream& operator>>(istream & in, BtsLogTime& btsLogTime);

private:
    void reorganizeOverflowValues();
    void reorganizeUnderflowValues();
    int m_years;
    int m_months;
    int m_days;
    int m_seconds;
    int m_microseconds;
};

}
