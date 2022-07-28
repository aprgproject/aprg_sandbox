#include "SolutionSet.hpp"

#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

SolutionSet::SolutionSet()
{}

bool SolutionSet::isEmpty() const
{
    return m_acceptedValues.empty() && m_rejectedValues.empty() && m_acceptedIntervals.empty();
}

AlbaNumbers const& SolutionSet::getAcceptedValues() const
{
    return m_acceptedValues;
}

AlbaNumbers const& SolutionSet::getRejectedValues() const
{
    return m_rejectedValues;
}

AlbaNumberIntervals const& SolutionSet::getAcceptedIntervals() const
{
    return m_acceptedIntervals;
}

string SolutionSet::getDisplayableString() const
{
    stringstream ss;
    if(!m_acceptedValues.empty())
    {
        ss << "AcceptedValues:{" << m_acceptedValues.front();
        for(unsigned int i=1; i<m_acceptedValues.size(); i++)
        {
            ss << ", " << m_acceptedValues.at(i);
        }
        ss << "} ";
    }
    if(!m_rejectedValues.empty())
    {
        ss << "RejectedValues:{" << m_rejectedValues.front();
        for(unsigned int i=1; i<m_rejectedValues.size(); i++)
        {
            ss << ", " << m_rejectedValues.at(i);
        }
        ss << "} ";
    }
    if(!m_acceptedIntervals.empty())
    {
        ss << "AcceptedInterval:{" << m_acceptedIntervals.front();
        for(unsigned int i=1; i<m_acceptedIntervals.size(); i++)
        {
            ss << ", " << m_acceptedIntervals.at(i);
        }
        ss << "}";
    }
    return ss.str();
}
void SolutionSet::addAcceptedValue(AlbaNumber const& value)
{
    m_acceptedValues.emplace_back(value);}

void SolutionSet::addAcceptedValues(AlbaNumbers const& values)
{
    m_acceptedValues.reserve(m_acceptedValues.size() + values.size());
    copy(values.cbegin(), values.cend(), back_inserter(m_acceptedValues));
}

void SolutionSet::addRejectedValue(AlbaNumber const& value)
{
    m_rejectedValues.emplace_back(value);
}

void SolutionSet::addRejectedValues(AlbaNumbers const& values)
{
    m_rejectedValues.reserve(m_rejectedValues.size() + values.size());
    copy(values.cbegin(), values.cend(), back_inserter(m_rejectedValues));
}

void SolutionSet::addAcceptedInterval(AlbaNumberInterval const& interval)
{
    m_acceptedIntervals.emplace_back(interval);
}

void SolutionSet::addValue(
        AlbaNumber const& value,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    if(isValueAcceptedFunction(value))
    {
        m_acceptedValues.emplace_back(value);
    }
    else
    {
        m_rejectedValues.emplace_back(value);
    }
}

void SolutionSet::determineAndAddAcceptedIntervals(
        AlbaNumbers const& additionalValuesToCheck,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    AlbaNumbers valuesToCheck(additionalValuesToCheck);
    prepareValuesToCheck(valuesToCheck);
    checkValuesAndPutIntervals(valuesToCheck, isValueAcceptedFunction);
    combineAcceptedIntervalsIfPossible();
}

void SolutionSet::prepareValuesToCheck(AlbaNumbers & valuesToCheck)
{
    valuesToCheck.reserve(valuesToCheck.size() + m_acceptedValues.size() + m_rejectedValues.size());
    copy(m_acceptedValues.cbegin(), m_acceptedValues.cend(), back_inserter(valuesToCheck));
    copy(m_rejectedValues.cbegin(), m_rejectedValues.cend(), back_inserter(valuesToCheck));
    valuesToCheck.erase(
                remove_if(
                    valuesToCheck.begin(),
                    valuesToCheck.end(),
                    [](AlbaNumber const& number){
                    return !number.isAFiniteValue() || number.isComplexNumberType();
                }),
            valuesToCheck.end());
    stable_sort(valuesToCheck.begin(), valuesToCheck.end());
}

void SolutionSet::checkValuesAndPutIntervals(
        AlbaNumbers const& valuesToCheck,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    if(!valuesToCheck.empty())
    {
        AlbaNumber const& firstValueToCheck(valuesToCheck.front());
        AlbaNumber intervalValueToCheck(firstValueToCheck - getAbsoluteValue(firstValueToCheck));
        addInterval(AlbaNumber::Value::NegativeInfinity, intervalValueToCheck, firstValueToCheck, isValueAcceptedFunction);
        AlbaNumber previousValueToCheck(firstValueToCheck);
        for(unsigned int i=1; i<valuesToCheck.size(); i++)
        {
            AlbaNumber const& valueToCheck(valuesToCheck.at(i));
            intervalValueToCheck = getAverage(previousValueToCheck, valueToCheck);
            addInterval(previousValueToCheck, intervalValueToCheck, valueToCheck, isValueAcceptedFunction);
            previousValueToCheck = valueToCheck;
        }
        intervalValueToCheck = previousValueToCheck + getAbsoluteValue(previousValueToCheck);
        addInterval(previousValueToCheck, intervalValueToCheck, AlbaNumber::Value::PositiveInfinity, isValueAcceptedFunction);
    }
}
void SolutionSet::addInterval(
        AlbaNumber const& lowerEndpointValue,
        AlbaNumber const& intervalValueToCheck,        AlbaNumber const& higherEndpointValue,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    if(isValueAcceptedFunction(intervalValueToCheck))
    {
        AlbaNumberIntervalEndpoint lowerEndpoint(createEndpoint(isValueAcceptedFunction(lowerEndpointValue), lowerEndpointValue));
        AlbaNumberIntervalEndpoint higherEndpoint(createEndpoint(isValueAcceptedFunction(higherEndpointValue), higherEndpointValue));
        if(lowerEndpointValue.isNegativeInfinity() || lowerEndpointValue.isPositiveInfinity())
        {
            lowerEndpoint.setType(AlbaNumberIntervalEndpoint::Type::Open);
        }
        if(higherEndpointValue.isNegativeInfinity() || higherEndpointValue.isPositiveInfinity())
        {
            higherEndpoint.setType(AlbaNumberIntervalEndpoint::Type::Open);
        }
        m_acceptedIntervals.emplace_back(lowerEndpoint, higherEndpoint);
    }
}

void SolutionSet::combineAcceptedIntervalsIfPossible()
{
    AlbaNumberIntervals intervals(m_acceptedIntervals);
    m_acceptedIntervals.clear();

    AlbaNumberIntervalOptional intervalToSaveOptional;
    for(AlbaNumberInterval const& interval : intervals)
    {
        if(intervalToSaveOptional.hasContent())
        {
            AlbaNumberInterval & intervalToSave(intervalToSaveOptional.getReference());
            if(intervalToSave.getHigherEndpoint().isClose()
                    && interval.getLowerEndpoint().isClose()
                    && intervalToSave.getHigherEndpoint().getValue() == interval.getLowerEndpoint().getValue())
            {
                intervalToSave.setNewEndpoint(interval.getHigherEndpoint());
            }
            else
            {
                m_acceptedIntervals.emplace_back(intervalToSave);
                intervalToSaveOptional.setConstReference(interval);
            }
        }
        else
        {
            intervalToSaveOptional.setConstReference(interval);
        }
    }
    if(intervalToSaveOptional.hasContent())
    {
        m_acceptedIntervals.emplace_back(intervalToSaveOptional.getReference());
    }
}

ostream & operator<<(ostream & out, SolutionSet const& solutionSet)
{
    out << solutionSet.getDisplayableString();
    return out;
}

}

}
