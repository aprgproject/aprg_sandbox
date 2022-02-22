#pragma once

#include <Common/Time/AlbaDateTime.hpp>

#include <string>
namespace wcdmaToolsBackend
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
    BtsLogTime(BtsLogTimeType logTimeType, std::string const& timeStampString);
    void clear();
    void setTimeByTimeStamp(BtsLogTimeType logTimeType, std::string const& timeStampString);
    bool isEmpty() const;
    bool isStartup() const;
    unsigned int getYears() const;
    unsigned int getMonths() const;
    unsigned int getDays() const;
    unsigned int getHours() const;
    unsigned int getMinutes() const;
    unsigned int getSeconds() const;
    unsigned int getTotalSeconds() const;
    unsigned int getMicroSeconds() const;
    void clearMicroSeconds();
    std::string getPrintableString() const;
    std::string getEquivalentStringPcTimeFormat() const;
    std::string getEquivalentStringBtsTimeFormat() const;
    bool operator<(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator>(BtsLogTime const& btsLogTimeToCompare) const;
    bool operator==(BtsLogTime const& btsLogTimeToCompare) const;
    BtsLogTime operator+(BtsLogTime const& btsLogTime) const;
    BtsLogTime operator-(BtsLogTime const& btsLogTime) const;
    friend std::ostream & operator<<(std::ostream & out, BtsLogTime const& btsLogTime);
    friend std::istream & operator>>(std::istream & in, BtsLogTime& btsLogTime);

private:
    alba::AlbaDateTime m_dateTime;
};

}
