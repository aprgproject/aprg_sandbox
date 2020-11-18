#pragma once

#include <string>
#include <ctime>

namespace alba
{

class AlbaDateTime
{
public:
    AlbaDateTime();
    AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
    void setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
    bool isEmpty() const;
    int getYears() const;
    int getMonths() const;
    int getDays() const;
    int getHours() const;
    int getMinutes() const;
    int getSeconds() const;
    int getTotalSeconds() const;
    int getMicroSeconds() const;
    std::string getPrintableString() const;
    bool operator<(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator>(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator==(AlbaDateTime const& btsLogTimeToCompare) const;
    bool operator!=(AlbaDateTime const& btsLogTimeToCompare) const;
    AlbaDateTime operator+(AlbaDateTime const& btsLogTime) const;
    AlbaDateTime operator-(AlbaDateTime const& btsLogTime) const;
private:
    void reorganizeOverflowValues();
    void reorganizeUnderflowValues();
    unsigned short int m_years;
    unsigned char m_months;
    unsigned char m_days;
    unsigned char m_hours;
    unsigned char m_minutes;
    unsigned char m_seconds;
    unsigned int m_microseconds;
};

}//namespace alba
