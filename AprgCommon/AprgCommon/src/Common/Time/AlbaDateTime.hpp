#pragma once

#include <Common/Bit/AlbaBitManipulation.hpp>

#include <cstdint>
#include <string>

namespace alba
{

using UInt32BitHelper = AlbaBitManipulation<uint32_t>;

class AlbaYearMonthDay
{
public:
    constexpr AlbaYearMonthDay()
        : m_yearMonthDay{}
    {}
    constexpr AlbaYearMonthDay(uint16_t const years, uint8_t const monthIndex, uint8_t const days)
        : m_yearMonthDay(convertToYearMonthDayFormat(years, monthIndex, days))
    {}

    static AlbaYearMonthDay createFromTotalDays(uint32_t const totalDays);

    void clear();
    uint32_t getYears() const;
    uint32_t getMonthIndex() const;
    uint32_t getDays() const;
    uint32_t getYearMonthDay() const;
    void setTime(uint32_t const totalDays);
    void setTime(uint16_t const years, uint8_t const monthIndex, uint8_t const days);

private:
    constexpr uint32_t convertToYearMonthDayFormat(uint16_t const years, uint8_t const monthIndex, uint8_t const days) const
    {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(years) | UInt32BitHelper::shiftBytesToTheLeft<1>(monthIndex) | days;
    }
    uint32_t m_yearMonthDay;
};


class AlbaHourMinuteSecond
{
public:
    constexpr AlbaHourMinuteSecond()
        : m_hourMinuteSecond{}
    {}
    constexpr AlbaHourMinuteSecond(uint8_t const hours, uint8_t const minutes, uint8_t const seconds)
        : m_hourMinuteSecond(convertToHourMinuteSecondFormat(hours, minutes, seconds))
    {}

    static AlbaHourMinuteSecond createFromTotalSeconds(uint32_t const totalSeconds);

    void clear();
    uint32_t getHours() const;
    uint32_t getMinutes() const;
    uint32_t getSeconds() const;
    uint32_t getHourMinuteSecond() const;
    void setTime(uint32_t const totalSeconds);
    void setTime(uint8_t const hours, uint8_t const minutes, uint8_t const seconds);

private:
    constexpr uint32_t convertToHourMinuteSecondFormat(uint8_t const hours, uint8_t const minutes, uint8_t const seconds) const
    {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(hours) | UInt32BitHelper::shiftBytesToTheLeft<1>(minutes) | seconds;
    }
    uint32_t m_hourMinuteSecond;
};


class AlbaDateTime
{
public:
    constexpr AlbaDateTime()
        : m_sign(1)
        , m_yearMonthDay{}
        , m_hourMinuteSecond{}
        , m_microseconds{}
    {}
    constexpr AlbaDateTime(
            AlbaYearMonthDay const& yearMonthDay,
            AlbaHourMinuteSecond const& hourMinuteSecond,
            uint32_t const microseconds)
        : m_sign(1)
        , m_yearMonthDay(yearMonthDay)
        , m_hourMinuteSecond(hourMinuteSecond)
        , m_microseconds(microseconds)
    {}
    constexpr AlbaDateTime(
            uint16_t const years,
            uint8_t const months,
            uint8_t const days,
            uint8_t const hours,
            uint8_t const minutes,
            uint8_t const seconds,
            uint32_t const microseconds)
        : m_sign(1)
        , m_yearMonthDay(years, convertMonthToCorrectMonthIndex(months), days)
        , m_hourMinuteSecond(hours, minutes, seconds)
        , m_microseconds(microseconds)
    {}

    static AlbaDateTime createFromTotalDaysAndSecondsAndMicroSeconds(
            uint32_t const totalDays,
            uint32_t const totalSeconds,
            uint32_t const totalMicroseconds);

    bool isEmpty() const;
    uint32_t getYears() const;
    uint32_t getMonths() const;
    uint32_t getDays() const;
    uint32_t getHours() const;
    uint32_t getMinutes() const;
    uint32_t getSeconds() const;
    uint32_t getMicroSeconds() const;
    void clearMicroSeconds();
    uint32_t getTotalDaysInYearMonthDays() const;
    uint32_t getTotalSecondsInHourMinutesSeconds() const;

    std::string getPrintableStringFormat1() const; //NN YYYY-MM-DD HH:MM:SS.MMMMMM
    std::string getPrintableStringFormat2() const; // HH:MM:SS
    std::string getPrintableStringFormat3() const; // HH:MM:SS.MMMMMM

    bool operator<(AlbaDateTime const& secondDateTime) const;
    bool operator>(AlbaDateTime const& secondDateTime) const;
    bool operator==(AlbaDateTime const& secondDateTime) const;
    bool operator!=(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator+(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator-(AlbaDateTime const& secondDateTime) const;

    void clear();
    void negate();
    void setTime(uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes, uint8_t const seconds, uint32_t const microseconds);
    void reorganizeValues(); // NOTE: This class needs to be manually reorganized since constructor is constexpr

private:

    constexpr uint8_t convertMonthToCorrectMonthIndex(uint8_t const month)
    {
        uint8_t result=0;
        if(month>=1 && month<=12)
        {
            result = month-1;
        }
        return result;
    }

    bool isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isGreaterThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime executeAddOrSubtract(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime addDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime subtractDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    int32_t m_sign; // sign is the hottest parameter (based from my evaluation)
    AlbaYearMonthDay m_yearMonthDay;
    AlbaHourMinuteSecond m_hourMinuteSecond;
    uint32_t m_microseconds;
};

}//namespace alba
