#pragma once

#include <string>

namespace alba
{

class AlbaDateTimeFormat
{
public:
    AlbaDateTimeFormat();
    AlbaDateTimeFormat(AlbaDateTimeFormatType logTimeType, std::string const& timeStampString);
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
    bool operator<(AlbaDateTimeFormat const& btsLogTimeToCompare) const;
    bool operator>(AlbaDateTimeFormat const& btsLogTimeToCompare) const;
    bool operator==(AlbaDateTimeFormat const& btsLogTimeToCompare) const;
    bool operator!=(AlbaDateTimeFormat const& btsLogTimeToCompare) const;
    AlbaDateTimeFormat operator+(AlbaDateTimeFormat const& btsLogTime) const;
    AlbaDateTimeFormat operator-(AlbaDateTimeFormat const& btsLogTime) const;
private:
    void reorganizeOverflowValues();
    void reorganizeUnderflowValues();
    int m_years;
    int m_months;
    int m_days;
    int m_seconds;
    int m_microseconds;
    bool m_isEmpty;
};

}//namespace alba
