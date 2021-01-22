#include "AlbaDateTime.hpp"

#include <Bit/AlbaBitManipulation.hpp>
#include <Time/AlbaDateTimeConstants.hpp>
#include <Time/AlbaDateTimeHelper.hpp>

#include <iomanip>
#include <sstream>

using namespace std;

namespace alba
{

AlbaYearMonthDay::AlbaYearMonthDay()
    : m_yearMonthDay(0)
{}

AlbaYearMonthDay::AlbaYearMonthDay(unsigned short int const years, unsigned char const months, unsigned char const days)
    : m_yearMonthDay(convertToYearMonthDayFormat(years, months, days))
{}

void AlbaYearMonthDay::clear()
{
    m_yearMonthDay = 0;
}

unsigned int AlbaYearMonthDay::getYears() const
{
    return DateTimeBitHelper::concatenateBytes(DateTimeBitHelper::getByteAt<3>(m_yearMonthDay) , DateTimeBitHelper::getByteAt<2>(m_yearMonthDay));
}

unsigned int AlbaYearMonthDay::getMonths() const
{
    return DateTimeBitHelper::getByteAt<1>(m_yearMonthDay);
}

unsigned int AlbaYearMonthDay::getDays() const
{
    return DateTimeBitHelper::getByteAt<0>(m_yearMonthDay);
}

unsigned int AlbaYearMonthDay::getYearMonthDay() const
{
    return m_yearMonthDay;
}

void AlbaYearMonthDay::setTime(unsigned int const totalDays)
{
    unsigned int remainingDays(totalDays);
    unsigned int years(dateTimeHelper::retrieveAndRemoveYearsFromTotalDays(remainingDays));
    unsigned int monthIndex(dateTimeHelper::retrieveAndRemoveMonthsFromTotalDays(remainingDays, years));
    setTime(years, monthIndex+1, remainingDays);
}

void AlbaYearMonthDay::setTime(unsigned short int const years, unsigned char const months, unsigned char const days)
{
    m_yearMonthDay = convertToYearMonthDayFormat(years, months, days);
}

unsigned int AlbaYearMonthDay::convertToYearMonthDayFormat(unsigned short int const years, unsigned char const months, unsigned char const days) const
{
    return DateTimeBitHelper::shiftLeft<2>(years) | DateTimeBitHelper::shiftLeft<1>(months) | days;
}


AlbaHourMinuteSecond::AlbaHourMinuteSecond()
    : m_hourMinuteSecond(0)
{}

AlbaHourMinuteSecond::AlbaHourMinuteSecond(unsigned char const hours, unsigned char const minutes, unsigned char const seconds)
    : m_hourMinuteSecond(convertToHourMinuteSecondFormat(hours, minutes, seconds))
{}

void AlbaHourMinuteSecond::clear()
{
    m_hourMinuteSecond = 0;
}

unsigned int AlbaHourMinuteSecond::getHours() const
{
    return DateTimeBitHelper::getByteAt<2>(m_hourMinuteSecond);
}

unsigned int AlbaHourMinuteSecond::getMinutes() const
{
    return DateTimeBitHelper::getByteAt<1>(m_hourMinuteSecond);
}

unsigned int AlbaHourMinuteSecond::getSeconds() const
{
    return DateTimeBitHelper::getByteAt<0>(m_hourMinuteSecond);
}

unsigned int AlbaHourMinuteSecond::getHourMinuteSecond() const
{
    return m_hourMinuteSecond;
}

void AlbaHourMinuteSecond::setTime(unsigned int const totalSeconds)
{
    unsigned int remainingSeconds(totalSeconds);
    unsigned int hours(dateTimeHelper::retrieveAndRemoveHoursFromTotalSeconds(remainingSeconds));
    unsigned int minutes(dateTimeHelper::retrieveAndRemoveMinutesFromTotalSeconds(remainingSeconds));
    setTime(hours, minutes, remainingSeconds);
}

void AlbaHourMinuteSecond::setTime(unsigned char const hours, unsigned char const minutes, unsigned char const seconds)
{
    m_hourMinuteSecond = convertToHourMinuteSecondFormat(hours, minutes, seconds);
}

unsigned int AlbaHourMinuteSecond::convertToHourMinuteSecondFormat(unsigned char const hours, unsigned char const minutes, unsigned char const seconds) const
{
    return DateTimeBitHelper::shiftLeft<2>(hours) | DateTimeBitHelper::shiftLeft<1>(minutes) | seconds;
}


AlbaDateTime::AlbaDateTime()
    : m_sign(1)
    , m_yearMonthDay()
    , m_hourMinuteSecond()
    , m_microseconds(0)
{}

AlbaDateTime::AlbaDateTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
    : m_sign(1)
    , m_yearMonthDay(years, months, days)
    , m_hourMinuteSecond(hours, minutes, seconds)
    , m_microseconds(microseconds)
{}

void AlbaDateTime::setTime(unsigned short int const years, unsigned char const months, unsigned char const days, unsigned char const hours, unsigned char const minutes, unsigned char const seconds, unsigned int const microseconds)
{
    m_sign = 1;
    m_yearMonthDay.setTime(years, months, days);
    m_hourMinuteSecond.setTime(hours, minutes, seconds);
    m_microseconds = microseconds;
}

void AlbaDateTime::clear()
{
    m_sign = 0;
    m_yearMonthDay.clear();
    m_hourMinuteSecond.clear();
    m_microseconds = 0;
}

bool AlbaDateTime::isEmpty() const
{
    return (m_yearMonthDay.getYearMonthDay()|m_hourMinuteSecond.getHourMinuteSecond()|m_microseconds)==0;
}

unsigned int AlbaDateTime::getYears() const
{
    return m_yearMonthDay.getYears();
}

unsigned int AlbaDateTime::getMonths() const
{
    return m_yearMonthDay.getMonths();
}

unsigned int AlbaDateTime::getDays() const
{
    return m_yearMonthDay.getDays();
}

unsigned int AlbaDateTime::getHours() const
{
    return m_hourMinuteSecond.getHours();
}

unsigned int AlbaDateTime::getMinutes() const
{
    return m_hourMinuteSecond.getMinutes();
}

unsigned int AlbaDateTime::getSeconds() const
{
    return m_hourMinuteSecond.getSeconds();
}

unsigned int AlbaDateTime::getMicroSeconds() const
{
    return m_microseconds;
}

void AlbaDateTime::clearMicroSeconds()
{
    m_microseconds=0;
}

unsigned int AlbaDateTime::getTotalDaysInYearMonthDays() const
{
    unsigned int years(getYears());    int monthIndex(getMonths()-1);
    unsigned int days(getDays());
    return dateTimeHelper::getTotalDays(years, monthIndex, days);
}
unsigned int AlbaDateTime::getTotalSecondsInHourMinutesSeconds() const
{
    return dateTimeHelper::getTotalSeconds(getHours(), getMinutes(), getSeconds());
}

string AlbaDateTime::getPrintableStringFormat1() const
{
    stringstream ss;
    ss << setfill(' ');
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

void AlbaDateTime::negate()
{
    m_sign*=-1;
}

AlbaDateTime AlbaDateTime::operator+(AlbaDateTime const& secondDateTime) const
{
    return executeAddOrSubtract(*this, secondDateTime);
}

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
    unsigned int totalDays(firstDateTime.getTotalDaysInYearMonthDays() + secondDateTime.getTotalDaysInYearMonthDays());
    unsigned int totalSeconds(firstDateTime.getTotalSecondsInHourMinutesSeconds() + secondDateTime.getTotalSecondsInHourMinutesSeconds());
    unsigned int totalMicroSeconds(firstDateTime.getMicroSeconds() + secondDateTime.getMicroSeconds());
    dateTimeHelper::reorganizeOverflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(totalDays);
    result.m_hourMinuteSecond.setTime(totalSeconds);
    result.m_microseconds = totalMicroSeconds;
    return result;
}

AlbaDateTime AlbaDateTime::subtractDateTimeMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const
{
    AlbaDateTime result;
    int totalDays((int)firstDateTime.getTotalDaysInYearMonthDays() - (int)secondDateTime.getTotalDaysInYearMonthDays());
    int totalSeconds((int)firstDateTime.getTotalSecondsInHourMinutesSeconds() - (int)secondDateTime.getTotalSecondsInHourMinutesSeconds());
    int totalMicroSeconds((int)firstDateTime.getMicroSeconds() - (int)secondDateTime.getMicroSeconds());
    dateTimeHelper::reorganizeUnderflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(totalDays);
    result.m_hourMinuteSecond.setTime(totalSeconds);
    result.m_microseconds = totalMicroSeconds;
    return result;
}

}//namespace alba
