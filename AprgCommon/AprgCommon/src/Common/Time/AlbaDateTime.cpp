#include "AlbaDateTime.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaDateTimeHelper.hpp>

#include <iomanip>
#include <sstream>

using namespace std;

namespace alba
{

AlbaYearMonthDay AlbaYearMonthDay::createFromTotalDays(
        uint32_t const totalDays)
{
    uint32_t remainingDays(totalDays);
    uint32_t years(dateTimeHelper::retrieveAndRemoveYearsFromTotalDays(remainingDays));
    uint32_t monthIndex(dateTimeHelper::retrieveAndRemoveMonthsFromTotalDays(remainingDays, years));
    return AlbaYearMonthDay(static_cast<uint16_t>(years), static_cast<uint8_t>(monthIndex), static_cast<uint8_t>(remainingDays));
}

void AlbaYearMonthDay::clear()
{
    m_yearMonthDay = 0;
}

uint32_t AlbaYearMonthDay::getYears() const
{
    return UInt32BitHelper::concatenateBytes(UInt32BitHelper::getByteAt<3>(m_yearMonthDay) , UInt32BitHelper::getByteAt<2>(m_yearMonthDay));
}

uint32_t AlbaYearMonthDay::getMonthIndex() const
{
    return UInt32BitHelper::getByteAt<1>(m_yearMonthDay);
}

uint32_t AlbaYearMonthDay::getDays() const
{
    return UInt32BitHelper::getByteAt<0>(m_yearMonthDay);
}

uint32_t AlbaYearMonthDay::getYearMonthDay() const
{
    return m_yearMonthDay;
}

void AlbaYearMonthDay::setTime(uint32_t const totalDays)
{
    uint32_t remainingDays(totalDays);
    uint32_t years(dateTimeHelper::retrieveAndRemoveYearsFromTotalDays(remainingDays));
    uint32_t monthIndex(dateTimeHelper::retrieveAndRemoveMonthsFromTotalDays(remainingDays, years));
    setTime(static_cast<uint16_t>(years),
            static_cast<uint8_t>(monthIndex),
            static_cast<uint8_t>(remainingDays));
}

void AlbaYearMonthDay::setTime(uint16_t const years, uint8_t const monthIndex, uint8_t const days)
{
    m_yearMonthDay = convertToYearMonthDayFormat(years, monthIndex, days);
}

AlbaHourMinuteSecond AlbaHourMinuteSecond::createFromTotalSeconds(
        uint32_t const totalSeconds)
{
    uint32_t remainingSeconds(totalSeconds);
    uint32_t hours(dateTimeHelper::retrieveAndRemoveHoursFromTotalSeconds(remainingSeconds));
    uint32_t minutes(dateTimeHelper::retrieveAndRemoveMinutesFromTotalSeconds(remainingSeconds));
    return AlbaHourMinuteSecond(static_cast<uint8_t>(hours), static_cast<uint8_t>(minutes), static_cast<uint8_t>(remainingSeconds));
}

void AlbaHourMinuteSecond::clear()
{
    m_hourMinuteSecond = 0;
}

uint32_t AlbaHourMinuteSecond::getHours() const
{
    return UInt32BitHelper::getByteAt<2>(m_hourMinuteSecond);
}

uint32_t AlbaHourMinuteSecond::getMinutes() const
{
    return UInt32BitHelper::getByteAt<1>(m_hourMinuteSecond);
}

uint32_t AlbaHourMinuteSecond::getSeconds() const
{
    return UInt32BitHelper::getByteAt<0>(m_hourMinuteSecond);
}

uint32_t AlbaHourMinuteSecond::getHourMinuteSecond() const
{
    return m_hourMinuteSecond;
}

void AlbaHourMinuteSecond::setTime(uint32_t const totalSeconds)
{
    uint32_t remainingSeconds(totalSeconds);
    uint32_t hours(dateTimeHelper::retrieveAndRemoveHoursFromTotalSeconds(remainingSeconds));
    uint32_t minutes(dateTimeHelper::retrieveAndRemoveMinutesFromTotalSeconds(remainingSeconds));
    setTime(static_cast<uint8_t>(hours),
            static_cast<uint8_t>(minutes),
            static_cast<uint8_t>(remainingSeconds));
}

void AlbaHourMinuteSecond::setTime(uint8_t const hours, uint8_t const minutes, uint8_t const seconds)
{
    m_hourMinuteSecond = convertToHourMinuteSecondFormat(hours, minutes, seconds);
}

void AlbaDateTime::setTime(uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes, uint8_t const seconds, uint32_t const microseconds)
{
    m_sign = 1;
    m_yearMonthDay.setTime(years, convertMonthToCorrectMonthIndex(months), days);    m_hourMinuteSecond.setTime(hours, minutes, seconds);
    m_microseconds = microseconds;
}

void AlbaDateTime::reorganizeValues()
{
    uint32_t totalDays(getTotalDaysInYearMonthDays());
    uint32_t totalSeconds(getTotalSecondsInHourMinutesSeconds());
    uint32_t totalMicroSeconds(getMicroSeconds());
    dateTimeHelper::reorganizeOverflowValues(totalDays, totalSeconds, totalMicroSeconds);
    m_yearMonthDay.setTime(totalDays);
    m_hourMinuteSecond.setTime(totalSeconds);
    m_microseconds = totalMicroSeconds;
}

AlbaDateTime AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(
        uint32_t const totalDays,
        uint32_t const totalSeconds,
        uint32_t const totalMicroseconds)
{
    return AlbaDateTime(AlbaYearMonthDay::createFromTotalDays(totalDays), AlbaHourMinuteSecond::createFromTotalSeconds(totalSeconds), totalMicroseconds);
}

bool AlbaDateTime::isEmpty() const{
    return (m_yearMonthDay.getYearMonthDay()|m_hourMinuteSecond.getHourMinuteSecond()|m_microseconds)==0;
}

uint32_t AlbaDateTime::getYears() const
{
    return m_yearMonthDay.getYears();
}

uint32_t AlbaDateTime::getMonths() const
{
    return m_yearMonthDay.getMonthIndex()+1;
}

uint32_t AlbaDateTime::getDays() const
{
    return m_yearMonthDay.getDays();
}

uint32_t AlbaDateTime::getHours() const
{
    return m_hourMinuteSecond.getHours();
}

uint32_t AlbaDateTime::getMinutes() const
{
    return m_hourMinuteSecond.getMinutes();
}

uint32_t AlbaDateTime::getSeconds() const
{
    return m_hourMinuteSecond.getSeconds();
}

uint32_t AlbaDateTime::getMicroSeconds() const
{
    return m_microseconds;
}
void AlbaDateTime::clearMicroSeconds()
{
    m_microseconds=0;
}

uint32_t AlbaDateTime::getTotalDaysInYearMonthDays() const
{
    uint32_t years(getYears());
    int32_t monthIndex(static_cast<int32_t>(getMonths())-1);
    uint32_t days(getDays());
    return dateTimeHelper::getTotalDays(years, static_cast<uint32_t>(monthIndex), days);
}

uint32_t AlbaDateTime::getTotalSecondsInHourMinutesSeconds() const
{
    return dateTimeHelper::getTotalSeconds(getHours(), getMinutes(), getSeconds());
}
string AlbaDateTime::getPrintableStringFormat1() const
{
    stringstream ss;    ss << setfill(' ');
    ss << setw(2) << m_sign << " * ";
    ss << setfill('0');
    ss << setw(4) << getYears() << "-";
    ss << setw(2) << getMonths() << "-";
    ss << setw(2) << getDays() << " ";
    ss << setw(2) << getHours() << ":";
    ss << setw(2) << getMinutes() << ":";
    ss << setw(2) << getSeconds() << ".";
    ss << setw(6) << getMicroSeconds();
    return ss.str();
}

string AlbaDateTime::getPrintableStringFormat2() const
{
    stringstream ss;
    ss << setfill('0');
    ss << setw(2) << getHours() << ":";
    ss << setw(2) << getMinutes() << ":";
    ss << setw(2) << getSeconds();
    return ss.str();
}

string AlbaDateTime::getPrintableStringFormat3() const
{
    stringstream ss;
    ss << setfill('0');
    ss << setw(2) << getHours() << ":";
    ss << setw(2) << getMinutes() << ":";
    ss << setw(2) << getSeconds() << ".";
    ss << setw(6) << getMicroSeconds();
    return ss.str();
}

bool AlbaDateTime::operator<(AlbaDateTime const& secondDateTime) const
{
    bool result(false);
    if(m_sign < secondDateTime.m_sign) result = true;
    else if(m_sign > secondDateTime.m_sign) result = false;
    else result = isLessThanInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator>(AlbaDateTime const& secondDateTime) const
{
    bool result(false);
    if(m_sign < secondDateTime.m_sign) result = false;
    else if(m_sign > secondDateTime.m_sign) result = true;
    else result = isGreaterThanInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator==(AlbaDateTime const& secondDateTime) const
{
    bool result(true);
    if(m_sign != secondDateTime.m_sign) result = false;
    else result = isEqualInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator!=(AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime const& firstDateTime(*this);
    return !(firstDateTime==secondDateTime);
}

void AlbaDateTime::clear()
{
    m_sign = 0;
    m_yearMonthDay.clear();
    m_hourMinuteSecond.clear();
    m_microseconds = 0;
}

void AlbaDateTime::negate()
{
    m_sign*=-1;}

AlbaDateTime AlbaDateTime::operator+(AlbaDateTime const& secondDateTime) const
{
    return executeAddOrSubtract(*this, secondDateTime);}

AlbaDateTime AlbaDateTime::operator-(AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime negateSecondDateTime(secondDateTime);
    negateSecondDateTime.negate();
    return executeAddOrSubtract(*this, negateSecondDateTime);
}

AlbaDateTime AlbaDateTime::executeAddOrSubtract(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime result;
    if(firstDateTime.m_sign == secondDateTime.m_sign)
    {
        result = addDateTimeMagnitude(firstDateTime, secondDateTime);
        result.m_sign = firstDateTime.m_sign;
    }
    else
    {
        if(isLessThanInMagnitude(firstDateTime, secondDateTime))
        {
            result = subtractDateTimeMagnitude(secondDateTime, firstDateTime);
            result.m_sign = secondDateTime.m_sign;
        }
        else
        {
            result = subtractDateTimeMagnitude(firstDateTime, secondDateTime);
            result.m_sign = firstDateTime.m_sign;
        }
    }
    return result;
}

bool AlbaDateTime::isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    bool result(false);
    if(firstDateTime.m_yearMonthDay.getYearMonthDay() < secondDateTime.m_yearMonthDay.getYearMonthDay()) result = true;
    else if(firstDateTime.m_yearMonthDay.getYearMonthDay() > secondDateTime.m_yearMonthDay.getYearMonthDay()) result = false;
    else if(firstDateTime.m_hourMinuteSecond.getHourMinuteSecond() < secondDateTime.m_hourMinuteSecond.getHourMinuteSecond()) result = true;
    else if(firstDateTime.m_hourMinuteSecond.getHourMinuteSecond() > secondDateTime.m_hourMinuteSecond.getHourMinuteSecond()) result = false;
    else if(firstDateTime.m_microseconds < secondDateTime.m_microseconds) result = true;
    else if(firstDateTime.m_microseconds > secondDateTime.m_microseconds) result = false;
    return result;
}

bool AlbaDateTime::isGreaterThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    bool result(false);
    if(firstDateTime.m_yearMonthDay.getYearMonthDay() < secondDateTime.m_yearMonthDay.getYearMonthDay()) result = false;
    else if(firstDateTime.m_yearMonthDay.getYearMonthDay() > secondDateTime.m_yearMonthDay.getYearMonthDay()) result = true;
    else if(firstDateTime.m_hourMinuteSecond.getHourMinuteSecond() < secondDateTime.m_hourMinuteSecond.getHourMinuteSecond()) result = false;
    else if(firstDateTime.m_hourMinuteSecond.getHourMinuteSecond() > secondDateTime.m_hourMinuteSecond.getHourMinuteSecond()) result = true;
    else if(firstDateTime.m_microseconds < secondDateTime.m_microseconds) result = false;
    else if(firstDateTime.m_microseconds > secondDateTime.m_microseconds) result = true;
    return result;
}

bool AlbaDateTime::isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    bool result(true);
    if(firstDateTime.m_yearMonthDay.getYearMonthDay() != secondDateTime.m_yearMonthDay.getYearMonthDay()) result = false;
    else if(firstDateTime.m_hourMinuteSecond.getHourMinuteSecond() != secondDateTime.m_hourMinuteSecond.getHourMinuteSecond()) result = false;
    else if(firstDateTime.m_microseconds != secondDateTime.m_microseconds) result = false;
    return result;
}

AlbaDateTime AlbaDateTime::addDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime result;
    uint32_t totalDays(firstDateTime.getTotalDaysInYearMonthDays() + secondDateTime.getTotalDaysInYearMonthDays());
    uint32_t totalSeconds(firstDateTime.getTotalSecondsInHourMinutesSeconds() + secondDateTime.getTotalSecondsInHourMinutesSeconds());
    uint32_t totalMicroSeconds(firstDateTime.getMicroSeconds() + secondDateTime.getMicroSeconds());
    dateTimeHelper::reorganizeOverflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(totalDays);
    result.m_hourMinuteSecond.setTime(totalSeconds);    result.m_microseconds = totalMicroSeconds;
    return result;
}

AlbaDateTime AlbaDateTime::subtractDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime result;
    int32_t totalDays(static_cast<int32_t>(firstDateTime.getTotalDaysInYearMonthDays()) - static_cast<int32_t>(secondDateTime.getTotalDaysInYearMonthDays()));
    int32_t totalSeconds(static_cast<int32_t>(firstDateTime.getTotalSecondsInHourMinutesSeconds()) - static_cast<int32_t>(secondDateTime.getTotalSecondsInHourMinutesSeconds()));
    int32_t totalMicroSeconds(static_cast<int32_t>(firstDateTime.getMicroSeconds()) - static_cast<int32_t>(secondDateTime.getMicroSeconds()));

    dateTimeHelper::reorganizeUnderflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(static_cast<uint32_t>(totalDays));
    result.m_hourMinuteSecond.setTime(static_cast<uint32_t>(totalSeconds));
    result.m_microseconds = static_cast<uint32_t>(totalMicroSeconds);
    return result;
}
}//namespace alba