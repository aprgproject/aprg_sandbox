#pragma once

#include <Bit/AlbaBitManipulation.hpp>

#include <string>

namespace alba
{

using DateTimeBitHelper = AlbaBitManipulation<unsigned int>;

class AlbaYearMonthDay
{
public:
    AlbaYearMonthDay();
    AlbaYearMonthDay(unsigned short int const years, unsigned char const months, unsigned char const days);
    unsigned int getYears() const;
    unsigned int getMonths() const;
    unsigned int getDays() const;
    unsigned int getYearMonthDay() const;
    void setTime(unsigned int const totalDays);
    void setTime(unsigned short int const years, unsigned char const months, unsigned char const days);
    unsigned int convertToYearMonthDayFormat(unsigned short int const years, unsigned char const months, unsigned char const days) const;
private:
    unsigned int m_yearMonthDay;
};

class AlbaHourMinuteSecond
{
public:
    AlbaHourMinuteSecond();
    AlbaHourMinuteSecond(unsigned char const hours, unsigned char const minutes, unsigned char const seconds);
    unsigned int getHours() const;
    unsigned int getMinutes() const;
    unsigned int getSeconds() const;
    unsigned int getHourMinuteSecond() const;
    void setTime(unsigned int const totalSeconds);
    void setTime(unsigned char const hours, unsigned char const minutes, unsigned char const seconds);
    unsigned int convertToHourMinuteSecondFormat(unsigned char const hours, unsigned char const minutes, unsigned char const seconds) const;
private:
    unsigned int m_hourMinuteSecond;
};

class AlbaDateTime
{
public:
    AlbaDateTime();
    AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
    bool isEmpty() const;
    unsigned int getYears() const;
    unsigned int getMonths() const;
    unsigned int getDays() const;
    unsigned int getHours() const;
    unsigned int getMinutes() const;
    unsigned int getSeconds() const;
    unsigned int getMicroSeconds() const;
    unsigned int getTotalDaysInYearMonthDays() const;
    unsigned int getTotalSecondsInHourMinutesSeconds() const;
    std::string getPrintableStringFormat1() const; //NN YYYY-MM-DD HH:MM:SS.MMMMMM
    bool operator<(AlbaDateTime const& secondDateTime) const;
    bool operator>(AlbaDateTime const& secondDateTime) const;
    bool operator==(AlbaDateTime const& secondDateTime) const;
    bool operator!=(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator+(AlbaDateTime const& btsLogTime) const;
    AlbaDateTime operator-(AlbaDateTime const& btsLogTime) const;
    void negate();
    void setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds);
private:
    bool isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isGreaterThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime executeAddOrSubtract(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime addDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime subtractDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    int m_sign;
    AlbaYearMonthDay m_yearMonthDay;
    AlbaHourMinuteSecond m_hourMinuteSecond;
    unsigned int m_microseconds;
};

}//namespace alba
