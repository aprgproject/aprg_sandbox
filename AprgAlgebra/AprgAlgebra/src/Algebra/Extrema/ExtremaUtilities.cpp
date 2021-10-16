#include "ExtremaUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Math/Number/Interval/AlbaNumberInterval.hpp>
using namespace alba::mathHelper;
using namespace alba::algebra::DomainAndRange;
using namespace std;
namespace alba
{

namespace algebra
{

bool willYieldToAbsoluteMaximumValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation)
{
    // f(c) is said to be the absolute maximum value of the f if c is in the domain of f and if f(c) >= f(x) for all values of x in the domain of f.

    AlbaNumbers valuesUsedForChecking;
    putArbitiaryValuesBasedFromDomainOfTerm(valuesUsedForChecking, term);
    return willYieldToExtremumValue(ExtremumType::Maximum, term, variableName, valueForEvaluation, valuesUsedForChecking);
}

bool willYieldToAbsoluteMinimumValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation)
{
    // f(c) is said to be the absolute minimum value of the f if c is in the domain of f and if f(c) <= f(x) for all values of x in the domain of f.

    AlbaNumbers valuesUsedForChecking;
    putArbitiaryValuesBasedFromDomainOfTerm(valuesUsedForChecking, term);
    return willYieldToExtremumValue(ExtremumType::Minimum, term, variableName, valueForEvaluation, valuesUsedForChecking);
}

bool willYieldToRelativeMaximumValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& openInterval)
{
    // The function f is aid to have a relative maximum value at c if there exists an open interval containing c,
    // on which f is defined such that f(c) >= f(x) for all x in this interval

    bool result(false);
    if(openInterval.getLowerEndpoint().isOpen()
            && openInterval.getHigherEndpoint().isOpen())
    {
        AlbaNumbers valuesUsedForChecking;
        putArbitiaryValuesFromInterval(valuesUsedForChecking, openInterval);
        result = willYieldToExtremumValue(ExtremumType::Maximum, term, variableName, valueForEvaluation, valuesUsedForChecking);
    }
    return result;}

bool willYieldToRelativeMinimumValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& openInterval)
{
    // The function f is aid to have a relative minimum value at c if there exists an open interval containing c,
    // on which f is defined such that f(c) <= f(x) for all x in this interval

    bool result(false);
    if(openInterval.getLowerEndpoint().isOpen()
            && openInterval.getHigherEndpoint().isOpen())
    {
        AlbaNumbers valuesUsedForChecking;
        putArbitiaryValuesFromInterval(valuesUsedForChecking, openInterval);
        return willYieldToExtremumValue(ExtremumType::Minimum, term, variableName, valueForEvaluation, valuesUsedForChecking);
    }
    return result;}

bool willYieldToExtremumValue(
        ExtremumType const extremumType,        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumbers const& valuesUsedForChecking)
{
    bool result(false);
    SubstitutionOfVariablesToValues substitutionOfC({{variableName, valueForEvaluation}});
    Term fOfC(substitutionOfC.performSubstitutionTo(term));
    if(fOfC.isConstant())
    {
        for(AlbaNumber const& valueUsedForChecking : valuesUsedForChecking)
        {
            SubstitutionOfVariablesToValues substitutionOfX({{variableName, valueUsedForChecking}});
            Term fOfX(substitutionOfX.performSubstitutionTo(term));
            if(fOfX.isConstant())
            {
                bool isMaximum(fOfC.getConstantValueConstReference() >= fOfX.getConstantValueConstReference());
                bool isMinimum(fOfC.getConstantValueConstReference() <= fOfX.getConstantValueConstReference());
                if((isMaximum && ExtremumType::Maximum == extremumType)
                        || (isMinimum && ExtremumType::Minimum == extremumType))
                {
                    result = true;
                }
                else
                {
                    result = false;
                    break;
                }
            }
        }
    }
    return result;
}

bool isDerivativeZeroOnExtremum(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueForEvaluation,
        AlbaNumberInterval const& interval)
{
    // If f(x) exists for all values of x in the open interval (a, b),
    // and if f has a relative extremum at c, where a<c<b and if f'(c) exists, then f'(c) = 0.

    Term derivative(getDerivativeAtUsingLimit(term, variableName, Term(valueForEvaluation), LimitAtAValueApproachType::BothSides));
    bool hasRelativeExtremum =
            willYieldToRelativeMaximumValue(term, variableName, valueForEvaluation, interval)
            || willYieldToRelativeMinimumValue(term, variableName, valueForEvaluation, interval);
    return hasRelativeExtremum
            && derivative.isConstant()
            && derivative.getConstantValueConstReference() == 0;
}

AlbaNumbers getCriticalNumbers(
        Term const& term,
        string const& variableName)
{
    // If c is a number in the domain of the function f, and if either f'(c) = 0 of f'(c) does not exist,
    // then c is called a critical number of f.

    Differentiation differentiation(variableName);
    Term derivative(differentiation.differentiate(term));
    Equation derivativeEquals0Equation(derivative, "=", Term(Constant(0)));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEquals0Equation));
    AlbaNumbers result;
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    result.reserve(acceptedValues.size() + rejectedValues.size());
    copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(result));
    copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(result));
    return result;
}

MinimumAndMaximum getMinimumAndMaximumAtClosedInterval(
        Term const& term,
        string const& variableName,
        AlbaNumberInterval const& closedInterval)
{
    // Extreme value theorem
    // If the function f is continuous on the closed interval [a, b],
    // then f has an absolute maximum value and an absolute minimum value on [a, b].

    // Procedure:
    // 1. Find the function values at the critical numbers on f on (a, b).
    // 2. Find the values of f(a) and f(b)
    // 3. The largest of the values from steps 1 and 2 is the absolute maximum value,
    // and the smallest of the values is the absolute minimum value.

    MinimumAndMaximum result;
    if(closedInterval.getLowerEndpoint().isClose()
            && closedInterval.getHigherEndpoint().isClose())
    {
        AlbaNumbers valuesToCheck(getCriticalNumbers(term, variableName));
        valuesToCheck.emplace_back(closedInterval.getLowerEndpoint().getValue());
        valuesToCheck.emplace_back(closedInterval.getHigherEndpoint().getValue());
        SubstitutionOfVariablesToValues substitution;
        bool isFirst(true);
        for(AlbaNumber const& valueToCheck : valuesToCheck)
        {
            substitution.putVariableWithValue(variableName, valueToCheck);
            Term evaluatedTerm(substitution.performSubstitutionTo(term));
            if(evaluatedTerm.isConstant())
            {
                AlbaNumber evaluatedValue(evaluatedTerm.getConstantValueConstReference());
                if(isFirst)
                {
                    result.minimumInputOutput.first = valueToCheck;
                    result.minimumInputOutput.second = evaluatedValue;
                    result.maximumInputOutput.first = valueToCheck;
                    result.maximumInputOutput.second = evaluatedValue;
                    isFirst = false;
                }
                else if(result.minimumInputOutput.second > evaluatedValue)
                {
                    result.minimumInputOutput.first = valueToCheck;
                    result.minimumInputOutput.second = evaluatedValue;
                }
                else if(result.maximumInputOutput.second < evaluatedValue)
                {
                    result.maximumInputOutput.first = valueToCheck;
                    result.maximumInputOutput.second = evaluatedValue;
                }
            }
        }
    }
    return result;
}

void putArbitiaryValuesBasedFromDomainOfTerm(
        AlbaNumbers & valuesUsedForChecking,
        Term const& term){
    SolutionSet domainSolutionSet = calculateDomainForTermWithOneVariable(term);
    AlbaNumberIntervals domains(domainSolutionSet.getAcceptedIntervals());
    for(AlbaNumberInterval const domain : domains)    {
        putArbitiaryValuesFromInterval(valuesUsedForChecking, domain);
    }
}

void putArbitiaryValuesFromInterval(
        AlbaNumbers & values,
        AlbaNumberInterval const& interval)
{
    AlbaNumberIntervalEndpoint lowEndpoint(interval.getLowerEndpoint());
    AlbaNumberIntervalEndpoint highEndpoint(interval.getHigherEndpoint());
    AlbaNumber lowValue(convertIfInfinityToNearestFiniteValue(lowEndpoint.getValue()));
    AlbaNumber highValue(convertIfInfinityToNearestFiniteValue(highEndpoint.getValue()));
    if(lowEndpoint.isClose())
    {
        values.emplace_back(lowValue);
    }
    if(highEndpoint.isClose())
    {
        values.emplace_back(highValue);
    }
    for(unsigned int level=0; level<5; level++)
    {
        AlbaNumber midpoint = (lowValue+highValue)/2;
        lowValue = (lowValue + midpoint)/2;
        highValue = (highValue + midpoint)/2;
        values.emplace_back(lowValue);
        values.emplace_back(midpoint);
        values.emplace_back(highValue);
    }
}

}

}
