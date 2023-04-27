#include "AlbaDateTime.hpp"

#include <Common/Bit/AlbaBitManipulation.hpp>
#include <Common/Time/AlbaDateTimeConstants.hpp>
#include <Common/Time/AlbaDateTimeHelper.hpp>

#include <iomanip>

using namespace std;

namespace alba {

AlbaYearMonthDay AlbaYearMonthDay::createFromTotalDays(uint32_t const totalDays) {
    uint32_t remainingDays(totalDays);
    uint32_t years(dateTimeHelper::getAndRemoveYearsFromNumberOfDays(remainingDays));
    uint32_t month(dateTimeHelper::getAndRemoveMonthsFromNumberOfDays(remainingDays, years));
    return AlbaYearMonthDay(
        static_cast<uint16_t>(years), static_cast<uint8_t>(month), static_cast<uint8_t>(remainingDays));
}

bool AlbaYearMonthDay::operator<(AlbaYearMonthDay const& second) const {
    return m_yearMonthDay < second.m_yearMonthDay;
}

bool AlbaYearMonthDay::operator>(AlbaYearMonthDay const& second) const {
    return m_yearMonthDay > second.m_yearMonthDay;
}

bool AlbaYearMonthDay::operator==(AlbaYearMonthDay const& second) const {
    return m_yearMonthDay == second.m_yearMonthDay;
}

bool AlbaYearMonthDay::operator!=(AlbaYearMonthDay const& second) const {
    return m_yearMonthDay != second.m_yearMonthDay;
}

bool AlbaYearMonthDay::isEmpty() const { return m_yearMonthDay == 0; }

uint32_t AlbaYearMonthDay::getYears() const {
    return UInt32BitHelper::concatenateBytes(
        UInt32BitHelper::getByteAt<3>(m_yearMonthDay), UInt32BitHelper::getByteAt<2>(m_yearMonthDay));
}

uint32_t AlbaYearMonthDay::getMonths() const { return UInt32BitHelper::getByteAt<1>(m_yearMonthDay); }

uint32_t AlbaYearMonthDay::getDays() const { return UInt32BitHelper::getByteAt<0>(m_yearMonthDay); }

uint32_t AlbaYearMonthDay::getTotalDays() const {
    return dateTimeHelper::getTotalDays(getYears(), getMonths(), getDays());
}

void AlbaYearMonthDay::clear() { m_yearMonthDay = 0; }

void AlbaYearMonthDay::setTime(uint32_t const totalDays) {
    uint32_t remainingDays(totalDays);
    uint32_t years(dateTimeHelper::getAndRemoveYearsFromNumberOfDays(remainingDays));
    uint32_t month(dateTimeHelper::getAndRemoveMonthsFromNumberOfDays(remainingDays, years));
    setTime(static_cast<uint16_t>(years), static_cast<uint8_t>(month), static_cast<uint8_t>(remainingDays));
}

void AlbaYearMonthDay::setTime(uint16_t const years, uint8_t const month, uint8_t const days) {
    m_yearMonthDay = convertToYearMonthDayFormat(years, month, days);
}

AlbaHourMinuteSecond AlbaHourMinuteSecond::createFromTotalSeconds(uint32_t const totalSeconds) {
    uint32_t remainingSeconds(totalSeconds);
    uint32_t hours(dateTimeHelper::getAndRemoveHoursFromNumberOfSeconds(remainingSeconds));
    uint32_t minutes(dateTimeHelper::getAndRemoveMinutesFromNumberOfSeconds(remainingSeconds));
    return AlbaHourMinuteSecond(
        static_cast<uint8_t>(hours), static_cast<uint8_t>(minutes), static_cast<uint8_t>(remainingSeconds));
}

bool AlbaHourMinuteSecond::operator<(AlbaHourMinuteSecond const& second) const {
    return m_hourMinuteSecond < second.m_hourMinuteSecond;
}

bool AlbaHourMinuteSecond::operator>(AlbaHourMinuteSecond const& second) const {
    return m_hourMinuteSecond > second.m_hourMinuteSecond;
}

bool AlbaHourMinuteSecond::operator==(AlbaHourMinuteSecond const& second) const {
    return m_hourMinuteSecond == second.m_hourMinuteSecond;
}

bool AlbaHourMinuteSecond::operator!=(AlbaHourMinuteSecond const& second) const {
    return m_hourMinuteSecond != second.m_hourMinuteSecond;
}

bool AlbaHourMinuteSecond::isEmpty() const { return m_hourMinuteSecond == 0; }

uint32_t AlbaHourMinuteSecond::getHours() const { return UInt32BitHelper::getByteAt<2>(m_hourMinuteSecond); }

uint32_t AlbaHourMinuteSecond::getMinutes() const { return UInt32BitHelper::getByteAt<1>(m_hourMinuteSecond); }

uint32_t AlbaHourMinuteSecond::getSeconds() const { return UInt32BitHelper::getByteAt<0>(m_hourMinuteSecond); }

uint32_t AlbaHourMinuteSecond::getTotalSeconds() const {
    return dateTimeHelper::getTotalSeconds(getHours(), getMinutes(), getSeconds());
}

void AlbaHourMinuteSecond::clear() { m_hourMinuteSecond = 0; }

void AlbaHourMinuteSecond::setTime(uint32_t const totalSeconds) {
    uint32_t remainingSeconds(totalSeconds);
    uint32_t hours(dateTimeHelper::getAndRemoveHoursFromNumberOfSeconds(remainingSeconds));
    uint32_t minutes(dateTimeHelper::getAndRemoveMinutesFromNumberOfSeconds(remainingSeconds));
    setTime(static_cast<uint8_t>(hours), static_cast<uint8_t>(minutes), static_cast<uint8_t>(remainingSeconds));
}

void AlbaHourMinuteSecond::setTime(uint8_t const hours, uint8_t const minutes, uint8_t const seconds) {
    m_hourMinuteSecond = convertToHourMinuteSecondFormat(hours, minutes, seconds);
}

void AlbaDateTime::setTime(
    uint16_t const years, uint8_t const months, uint8_t const days, uint8_t const hours, uint8_t const minutes,
    uint8_t const seconds, uint32_t const microseconds) {
    m_sign = 1;
    m_yearMonthDay.setTime(years, months, days);
    m_hourMinuteSecond.setTime(hours, minutes, seconds);
    m_microseconds = microseconds;
}

void AlbaDateTime::reorganizeValues() {
    uint32_t totalDays(getYearMonthDay().getTotalDays());
    uint32_t totalSeconds(getHourMinutesSecond().getTotalSeconds());
    uint32_t totalMicroSeconds(getMicroSeconds());
    dateTimeHelper::reorganizeOverflowValues(totalDays, totalSeconds, totalMicroSeconds);
    m_yearMonthDay.setTime(totalDays);
    m_hourMinuteSecond.setTime(totalSeconds);
    m_microseconds = totalMicroSeconds;
}

AlbaDateTime AlbaDateTime::createFromTotalDaysAndSecondsAndMicroSeconds(
    uint32_t const totalDays, uint32_t const totalSeconds, uint32_t const totalMicroseconds) {
    return AlbaDateTime(
        AlbaYearMonthDay::createFromTotalDays(totalDays), AlbaHourMinuteSecond::createFromTotalSeconds(totalSeconds),
        totalMicroseconds);
}

bool AlbaDateTime::isEmpty() const {
    return m_yearMonthDay.isEmpty() || m_hourMinuteSecond.isEmpty() || m_microseconds == 0;
}

uint32_t AlbaDateTime::getYears() const { return m_yearMonthDay.getYears(); }

uint32_t AlbaDateTime::getMonths() const { return m_yearMonthDay.getMonths(); }

uint32_t AlbaDateTime::getDays() const { return m_yearMonthDay.getDays(); }

uint32_t AlbaDateTime::getHours() const { return m_hourMinuteSecond.getHours(); }

uint32_t AlbaDateTime::getMinutes() const { return m_hourMinuteSecond.getMinutes(); }

uint32_t AlbaDateTime::getSeconds() const { return m_hourMinuteSecond.getSeconds(); }

uint32_t AlbaDateTime::getMicroSeconds() const { return m_microseconds; }

AlbaYearMonthDay const& AlbaDateTime::getYearMonthDay() const { return m_yearMonthDay; }

AlbaHourMinuteSecond const& AlbaDateTime::getHourMinutesSecond() const { return m_hourMinuteSecond; }

AlbaYearMonthDay& AlbaDateTime::getYearMonthDayReference() { return m_yearMonthDay; }

AlbaHourMinuteSecond& AlbaDateTime::getHourMinutesSecondReference() { return m_hourMinuteSecond; }

uint32_t& AlbaDateTime::getMicroSecondsReference() { return m_microseconds; }

bool AlbaDateTime::operator<(AlbaDateTime const& secondDateTime) const {
    bool result(false);
    if (m_sign < secondDateTime.m_sign)
        result = true;
    else if (m_sign > secondDateTime.m_sign)
        result = false;
    else
        result = isLessThanInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator>(AlbaDateTime const& secondDateTime) const {
    bool result(false);
    if (m_sign < secondDateTime.m_sign)
        result = false;
    else if (m_sign > secondDateTime.m_sign)
        result = true;
    else
        result = isGreaterThanInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator==(AlbaDateTime const& secondDateTime) const {
    bool result(true);
    if (m_sign != secondDateTime.m_sign)
        result = false;
    else
        result = isEqualInMagnitude(*this, secondDateTime);
    return result;
}

bool AlbaDateTime::operator!=(AlbaDateTime const& secondDateTime) const {
    AlbaDateTime const& firstDateTime(*this);
    return !(firstDateTime == secondDateTime);
}

void AlbaDateTime::clear() {
    m_sign = 0;
    m_yearMonthDay.clear();
    m_hourMinuteSecond.clear();
    m_microseconds = 0;
}

void AlbaDateTime::negate() { m_sign *= -1; }

AlbaDateTime AlbaDateTime::operator+(AlbaDateTime const& secondDateTime) const {
    return executeAddOrSubtract(*this, secondDateTime);
}

AlbaDateTime AlbaDateTime::operator-(AlbaDateTime const& secondDateTime) const {
    AlbaDateTime negateSecondDateTime(secondDateTime);
    negateSecondDateTime.negate();
    return executeAddOrSubtract(*this, negateSecondDateTime);
}

AlbaDateTime AlbaDateTime::executeAddOrSubtract(
    AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    AlbaDateTime result;
    if (firstDateTime.m_sign == secondDateTime.m_sign) {
        result = addDateTimeMagnitude(firstDateTime, secondDateTime);
        result.m_sign = firstDateTime.m_sign;
    } else {
        if (isLessThanInMagnitude(firstDateTime, secondDateTime)) {
            result = subtractDateTimeMagnitude(secondDateTime, firstDateTime);
            result.m_sign = secondDateTime.m_sign;
        } else {
            result = subtractDateTimeMagnitude(firstDateTime, secondDateTime);
            result.m_sign = firstDateTime.m_sign;
        }
    }
    return result;
}

bool AlbaDateTime::isLessThanInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    return tie(firstDateTime.m_yearMonthDay, firstDateTime.m_hourMinuteSecond, firstDateTime.m_microseconds) <
           tie(secondDateTime.m_yearMonthDay, secondDateTime.m_hourMinuteSecond, secondDateTime.m_microseconds);
}

bool AlbaDateTime::isGreaterThanInMagnitude(
    AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    return tie(firstDateTime.m_yearMonthDay, firstDateTime.m_hourMinuteSecond, firstDateTime.m_microseconds) >
           tie(secondDateTime.m_yearMonthDay, secondDateTime.m_hourMinuteSecond, secondDateTime.m_microseconds);
}

bool AlbaDateTime::isEqualInMagnitude(AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    return tie(firstDateTime.m_yearMonthDay, firstDateTime.m_hourMinuteSecond, firstDateTime.m_microseconds) ==
           tie(secondDateTime.m_yearMonthDay, secondDateTime.m_hourMinuteSecond, secondDateTime.m_microseconds);
}

AlbaDateTime AlbaDateTime::addDateTimeMagnitude(
    AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    AlbaDateTime result;
    uint32_t totalDays(
        firstDateTime.getYearMonthDay().getTotalDays() + secondDateTime.getYearMonthDay().getTotalDays());
    uint32_t totalSeconds(
        firstDateTime.getHourMinutesSecond().getTotalSeconds() +
        secondDateTime.getHourMinutesSecond().getTotalSeconds());
    uint32_t totalMicroSeconds(firstDateTime.getMicroSeconds() + secondDateTime.getMicroSeconds());
    dateTimeHelper::reorganizeOverflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(totalDays);
    result.m_hourMinuteSecond.setTime(totalSeconds);
    result.m_microseconds = totalMicroSeconds;
    return result;
}

AlbaDateTime AlbaDateTime::subtractDateTimeMagnitude(
    AlbaDateTime const& firstDateTime, AlbaDateTime const& secondDateTime) const {
    AlbaDateTime result;
    int32_t totalDays(
        static_cast<int32_t>(firstDateTime.getYearMonthDay().getTotalDays()) -
        static_cast<int32_t>(secondDateTime.getYearMonthDay().getTotalDays()));
    int32_t totalSeconds(
        static_cast<int32_t>(firstDateTime.getHourMinutesSecond().getTotalSeconds()) -
        static_cast<int32_t>(secondDateTime.getHourMinutesSecond().getTotalSeconds()));
    int32_t totalMicroSeconds(
        static_cast<int32_t>(firstDateTime.getMicroSeconds()) - static_cast<int32_t>(secondDateTime.getMicroSeconds()));

    dateTimeHelper::reorganizeUnderflowValues(totalDays, totalSeconds, totalMicroSeconds);
    result.m_yearMonthDay.setTime(static_cast<uint32_t>(totalDays));
    result.m_hourMinuteSecond.setTime(static_cast<uint32_t>(totalSeconds));
    result.m_microseconds = static_cast<uint32_t>(totalMicroSeconds);
    return result;
}

template <AlbaDateTime::PrintFormat printFormat>
ostream& operator<<(ostream& out, AlbaDateTime::PrintObject<printFormat> const&) {
    using PrintObjectWithFormat = AlbaDateTime::PrintObject<printFormat>;
    static_assert(
        sizeof(PrintObjectWithFormat) == -1,
        "This print format is not supported. Please add a specialization if needed.");
    return out;
}

template <>
ostream& operator<<(ostream& out, AlbaDateTime::PrintObject<AlbaDateTime::PrintFormat::Type1> const& printObject) {
    AlbaDateTime const& dateTime(*printObject.dateTimePointer);
    out << setfill(' ');
    out << setw(2) << dateTime.m_sign << " * ";
    out << setfill('0');
    out << setw(4) << dateTime.getYears() << "-";
    out << setw(2) << dateTime.getMonths() << "-";
    out << setw(2) << dateTime.getDays() << " ";
    out << setw(2) << dateTime.getHours() << ":";
    out << setw(2) << dateTime.getMinutes() << ":";
    out << setw(2) << dateTime.getSeconds() << ".";
    out << setw(6) << dateTime.getMicroSeconds();
    return out;
}

template <>
ostream& operator<<(ostream& out, AlbaDateTime::PrintObject<AlbaDateTime::PrintFormat::Type2> const& printObject) {
    AlbaDateTime const& dateTime(*printObject.dateTimePointer);
    out << setfill('0');
    out << setw(2) << dateTime.getHours() << ":";
    out << setw(2) << dateTime.getMinutes() << ":";
    out << setw(2) << dateTime.getSeconds();
    return out;
}

template <>
ostream& operator<<(ostream& out, AlbaDateTime::PrintObject<AlbaDateTime::PrintFormat::Type3> const& printObject) {
    AlbaDateTime const& dateTime(*printObject.dateTimePointer);
    out << setfill('0');
    out << setw(2) << dateTime.getHours() << ":";
    out << setw(2) << dateTime.getMinutes() << ":";
    out << setw(2) << dateTime.getSeconds() << ".";
    out << setw(6) << dateTime.getMicroSeconds();
    return out;
}

ostream& operator<<(ostream& out, AlbaDateTime const& dateTime) {
    out << dateTime.getPrintObject<AlbaDateTime::PrintFormat::Type1>();
    return out;
}

}  // namespace alba
