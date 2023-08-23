#pragma once

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Time/AlbaDateTimeConstants.hpp>

#include <cstdint>
#include <ostream>

namespace alba {

using UInt32BitHelper = AlbaBitManipulation<uint32_t>;

class AlbaYearMonthDay {
public:
    constexpr AlbaYearMonthDay() : m_yearMonthDay{} {}
    constexpr AlbaYearMonthDay(uint16_t const years, uint8_t const month, uint8_t const days)
        : m_yearMonthDay(convertToYearMonthDayFormat(years, month, days)) {}

    // rule of zero

    static AlbaYearMonthDay createFromTotalDays(uint32_t const totalDays);

    bool operator<(AlbaYearMonthDay const& second) const;
    bool operator>(AlbaYearMonthDay const& second) const;
    bool operator==(AlbaYearMonthDay const& second) const;
    bool operator!=(AlbaYearMonthDay const& second) const;

    bool isEmpty() const;
    uint32_t getYears() const;
    uint32_t getMonths() const;
    uint32_t getDays() const;
    uint32_t getTotalDays() const;
    AlbaDateTimeConstants::DayOfTheWeek getDayOfTheWeek() const;

    void clear();
    void setTime(uint32_t const totalDays);
    void setTime(uint16_t const years, uint8_t const month, uint8_t const days);

private:
    constexpr uint32_t convertToYearMonthDayFormat(
        uint16_t const years, uint8_t const month, uint8_t const days) const {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(years) | UInt32BitHelper::shiftBytesToTheLeft<1>(month) | days;
    }
    uint32_t m_yearMonthDay;
};

class AlbaHourMinuteSecond {
public:
    constexpr AlbaHourMinuteSecond() : m_hourMinuteSecond{} {}
    constexpr AlbaHourMinuteSecond(uint8_t const hours, uint8_t const minutes, uint8_t const seconds)
        : m_hourMinuteSecond(convertToHourMinuteSecondFormat(hours, minutes, seconds)) {}

    // rule of zero

    static AlbaHourMinuteSecond createFromTotalSeconds(uint32_t const totalSeconds);

    bool operator<(AlbaHourMinuteSecond const& second) const;
    bool operator>(AlbaHourMinuteSecond const& second) const;
    bool operator==(AlbaHourMinuteSecond const& second) const;
    bool operator!=(AlbaHourMinuteSecond const& second) const;

    bool isEmpty() const;
    uint32_t getHours() const;
    uint32_t getMinutes() const;
    uint32_t getSeconds() const;
    uint32_t getTotalSeconds() const;

    void clear();
    void setTime(uint32_t const totalSeconds);
    void setTime(uint8_t const hours, uint8_t const minutes, uint8_t const seconds);

private:
    constexpr uint32_t convertToHourMinuteSecondFormat(
        uint8_t const hours, uint8_t const minutes, uint8_t const seconds) const {
        return UInt32BitHelper::shiftBytesToTheLeft<2>(hours) | UInt32BitHelper::shiftBytesToTheLeft<1>(minutes) |
               seconds;
    }
    uint32_t m_hourMinuteSecond;
};

class AlbaDateTime {
public:
    enum class PrintFormat {
        Type1,  // NN YYYY-MM-DD HH:MM:SS.MMMMMM
        Type2,  // HH:MM:SS
        Type3   // HH:MM:SS.MMMMMM
    };

    template <PrintFormat printFormat>
    struct PrintObject {
        explicit PrintObject(AlbaDateTime const& dataTimeToPrint) : savedDateTime(dataTimeToPrint) {}
        AlbaDateTime const& savedDateTime;
    };

    constexpr AlbaDateTime() : m_sign(1), m_yearMonthDay{}, m_hourMinuteSecond{}, m_microseconds{} {}    constexpr AlbaDateTime(
        AlbaYearMonthDay const& yearMonthDay, AlbaHourMinuteSecond const& hourMinuteSecond, uint32_t const microseconds)
        : m_sign(1), m_yearMonthDay(yearMonthDay), m_hourMinuteSecond(hourMinuteSecond), m_microseconds(microseconds) {}
    constexpr AlbaDateTime(        uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes,
        uint8_t const seconds, uint32_t const microseconds)
        : m_sign(1),
          m_yearMonthDay(years, months, days),
          m_hourMinuteSecond(hours, minutes, seconds),
          m_microseconds(microseconds) {}

    // rule of zero

    static AlbaDateTime createFromTotalDaysAndSecondsAndMicroSeconds(
        uint32_t const totalDays, uint32_t const totalSeconds, uint32_t const totalMicroseconds);

    bool operator<(AlbaDateTime const& secondDateTime) const;
    bool operator>(AlbaDateTime const& secondDateTime) const;
    bool operator==(AlbaDateTime const& secondDateTime) const;
    bool operator!=(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator+(AlbaDateTime const& secondDateTime) const;
    AlbaDateTime operator-(AlbaDateTime const& secondDateTime) const;

    bool isEmpty() const;
    uint32_t getYears() const;
    uint32_t getMonths() const;
    uint32_t getDays() const;
    uint32_t getHours() const;
    uint32_t getMinutes() const;
    uint32_t getSeconds() const;
    uint32_t getMicroSeconds() const;
    AlbaYearMonthDay const& getYearMonthDay() const;
    AlbaHourMinuteSecond const& getHourMinutesSecond() const;

    AlbaYearMonthDay& getYearMonthDayReference();
    AlbaHourMinuteSecond& getHourMinutesSecondReference();
    uint32_t& getMicroSecondsReference();

    void clear();
    void negate();
    void setTime(
        uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes,
        uint8_t const seconds, uint32_t const microseconds);
    void reorganizeValues();  // NOTE: AlbaDateTime class needs to be manually reorganized (if needed) since the
                              // constructor is constexpr.

    template <PrintFormat printFormat>
    PrintObject<printFormat> getPrintObject() const {
        return PrintObject<printFormat>(*this);
    }

private:    bool isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isGreaterThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    bool isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime executeAddOrSubtract(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;    AlbaDateTime addDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;
    AlbaDateTime subtractDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const;

    template <PrintFormat printFormat>
    friend std::ostream& operator<<(std::ostream& out, AlbaDateTime::PrintObject<printFormat> const&);
    friend std::ostream& operator<<(std::ostream& out, AlbaDateTime const& dateTime);

    int32_t m_sign;  // sign is the hottest parameter (based from my evaluation)
    AlbaYearMonthDay m_yearMonthDay;
    AlbaHourMinuteSecond m_hourMinuteSecond;
    uint32_t m_microseconds;
};

}  // namespace alba
