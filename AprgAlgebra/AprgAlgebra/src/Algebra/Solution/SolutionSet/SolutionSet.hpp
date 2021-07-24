#pragma once

#include <Math/AlbaNumberTypes.hpp>

#include <functional>

namespace alba
{

namespace algebra
{

class SolutionSet
{
public:
    SolutionSet();

    using FunctionForCheckingValues = std::function<bool(AlbaNumber const&)>;

    AlbaNumbers const& getAcceptedValues() const;
    AlbaNumbers const& getRejectedValues() const;
    AlbaNumberIntervals const& getAcceptedIntervals() const;

    void addAcceptedValue(AlbaNumber const& value);
    void addRejectedValue(AlbaNumber const& value);
    void addValue(
            AlbaNumber const& value,
            FunctionForCheckingValues const& isValueAcceptedFunction);
    void determineAndAddAcceptedIntervals(
            AlbaNumbers const& valuesToCheck,
            FunctionForCheckingValues const& isValueAcceptedFunction);

private:
    void prepareValuesToCheck(AlbaNumbers & combinedValuesToCheck);
    void checkValuesAndPutIntervals(
            AlbaNumbers const& valuesToCheck,
            FunctionForCheckingValues const& isValueAcceptedFunction);
    void addInterval(
            AlbaNumber const& lowerEndpointValue,
            AlbaNumber const& intervalValueToCheck,
            AlbaNumber const& higherEndpointValue,
            FunctionForCheckingValues const& isValueAcceptedFunction);
    void combineAcceptedIntervalsIfPossible();
    AlbaNumbers m_acceptedValues;
    AlbaNumbers m_rejectedValues;
    AlbaNumberIntervals m_acceptedIntervals;
};


}

}
