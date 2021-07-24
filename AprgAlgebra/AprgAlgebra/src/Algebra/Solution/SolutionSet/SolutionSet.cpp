#include "SolutionSet.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

SolutionSet::SolutionSet()
{}

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

void SolutionSet::addAcceptedValue(AlbaNumber const& value)
{
    m_acceptedValues.emplace_back(value);
}

void SolutionSet::addRejectedValue(AlbaNumber const& value)
{
    m_rejectedValues.emplace_back(value);
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
        AlbaNumbers const& addedValuesToCheck,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    AlbaNumbers valuesToCheck(addedValuesToCheck);
    prepareValuesToCheck(valuesToCheck);
    checkValuesAndPutIntervals(valuesToCheck, isValueAcceptedFunction);
    combineAcceptedIntervalsIfPossible();
}

void SolutionSet::prepareValuesToCheck(AlbaNumbers & valuesToCheck)
{
    copy(m_acceptedValues.cbegin(), m_acceptedValues.cend(), back_inserter(valuesToCheck));
    copy(m_rejectedValues.cbegin(), m_rejectedValues.cend(), back_inserter(valuesToCheck));
    valuesToCheck.erase(
                remove_if(
                    valuesToCheck.begin(),
                    valuesToCheck.end(),
                    [](AlbaNumber const& number){
                    return number.isPositiveInfinity() || number.isNegativeInfinity();
                }),
            valuesToCheck.end());
    stable_sort(valuesToCheck.begin(), valuesToCheck.end());
}

void SolutionSet::checkValuesAndPutIntervals(
        AlbaNumbers const& valuesToCheck,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    bool isFirst(true);
    AlbaNumber previousValueToCheck(AlbaNumber::Value::NegativeInfinity);
    for(AlbaNumber const& valueToCheck : valuesToCheck)
    {
        if(isFirst)
        {
            AlbaNumber intervalValueToCheck(valueToCheck-getAbsoluteValue(valueToCheck));
            addInterval(AlbaNumber(AlbaNumber::Value::NegativeInfinity), intervalValueToCheck, valueToCheck, isValueAcceptedFunction);
            isFirst=false;
        }
        else
        {
            AlbaNumber intervalValueToCheck(getAverage(previousValueToCheck, valueToCheck));
            addInterval(previousValueToCheck, intervalValueToCheck, valueToCheck, isValueAcceptedFunction);
        }
        previousValueToCheck = valueToCheck;
    }
    if(!valuesToCheck.empty())
    {
        AlbaNumber intervalValueToCheck(previousValueToCheck+getAbsoluteValue(previousValueToCheck));
        addInterval(previousValueToCheck, intervalValueToCheck, AlbaNumber(AlbaNumber::Value::PositiveInfinity), isValueAcceptedFunction);
    }
}

void SolutionSet::addInterval(
        AlbaNumber const& lowerEndpointValue,
        AlbaNumber const& intervalValueToCheck,
        AlbaNumber const& higherEndpointValue,
        FunctionForCheckingValues const& isValueAcceptedFunction)
{
    if(isValueAcceptedFunction(intervalValueToCheck))
    {
        AlbaNumberIntervalEndpoint lowerEndpoint(createEndpoint(lowerEndpointValue, isValueAcceptedFunction(lowerEndpointValue)));
        AlbaNumberIntervalEndpoint higherEndpoint(createEndpoint(higherEndpointValue, isValueAcceptedFunction(higherEndpointValue)));
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

}

}
