#include "ExtremaUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Differentiation/DifferentiationUtilities.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Math/Number/Interval/AlbaNumberInterval.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::mathHelper;
using namespace alba::algebra::DomainAndRange;
using namespace std;

namespace alba
{

namespace algebra
{

//functions for this file only
namespace
{

void putArbitiaryValuesFromInterval(AlbaNumbers & arbitiaryValues, AlbaNumberInterval const& interval);
void putArbitiaryValuesBasedFromDomainOfTerm(AlbaNumbers & arbitiaryValues, Term const& term);

}

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
    return result;
}

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
    return result;
}

bool willYieldToExtremumValue(
        ExtremumType const extremumType,
        Term const& term,
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

bool isDerivativeZeroOnPossibleExtremum(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueAtPossibleExtremum,
        AlbaNumberInterval const& interval)
{
    // If f(x) exists for all values of x in the open interval (a, b),
    // and if f has a relative extremum at c, where a<c<b and if f'(c) exists, then f'(c) = 0.

    Term derivative(getDerivativeAtUsingLimit(term, variableName, Term(valueAtPossibleExtremum), LimitAtAValueApproachType::BothSides));
    bool hasRelativeExtremum =
            willYieldToRelativeMaximumValue(term, variableName, valueAtPossibleExtremum, interval)
            || willYieldToRelativeMinimumValue(term, variableName, valueAtPossibleExtremum, interval);
    return hasRelativeExtremum
            && derivative.isConstant()
            && derivative.getConstantValueConstReference() == 0;
}

bool isDecreasingAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    Differentiation differentiation(variableName);
    Term firstDerivativeTerm(differentiation.differentiate(term));
    SubstitutionOfVariablesToValues substitution({{variableName, value}});
    Term firstDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if(firstDerivativeValue.isConstant())
    {
        result = firstDerivativeValue.getConstantValueConstReference() < 0;
    }
    return result;
}

bool isIncreasingAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    Differentiation differentiation(variableName);
    Term firstDerivativeTerm(differentiation.differentiate(term));
    SubstitutionOfVariablesToValues substitution({{variableName, value}});
    Term firstDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if(firstDerivativeValue.isConstant())
    {
        result = firstDerivativeValue.getConstantValueConstReference() > 0;
    }
    return result;
}

bool isConcaveDownwardAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    Differentiation differentiation(variableName);
    Term secondDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    SubstitutionOfVariablesToValues substitution({{variableName, value}});
    Term secondDerivativeValue(substitution.performSubstitutionTo(secondDerivativeTerm));
    bool result(false);
    if(secondDerivativeValue.isConstant())
    {
        result = secondDerivativeValue.getConstantValueConstReference() < 0;
    }
    return result;
}

bool isConcaveUpwardAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    Differentiation differentiation(variableName);
    Term firstDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    SubstitutionOfVariablesToValues substitution({{variableName, value}});
    Term secondDerivativeValue(substitution.performSubstitutionTo(firstDerivativeTerm));
    bool result(false);
    if(secondDerivativeValue.isConstant())
    {
        result = secondDerivativeValue.getConstantValueConstReference() > 0;
    }
    return result;
}

bool hasPointOfInflectionAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    // The point (c, f(c)) is a point of inflection of the graph of the function f if the graph has a tangent line there,
    // and if there exists an open interval I containing c such that if x is in I, the either:
    // (i) f''(x) < 0 if x < c, and f''(x) > 0 if x > c, or
    // (ii) f''(x) > 0 if x < c, and f''(x) < 0 if x > c

    Differentiation differentiation(variableName);
    Term secondDerivativeTerm(differentiation.differentiateMultipleTimes(term, 2));
    bool result(false);
    if(!secondDerivativeTerm.isConstant())
    {
        SubstitutionOfVariablesToValues substitution({{variableName, value}});
        Term secondDerivativeValue(substitution.performSubstitutionTo(secondDerivativeTerm));
        if(secondDerivativeValue.isConstant())
        {
            result = secondDerivativeValue.getConstantValueConstReference() == 0;
        }
    }
    return result;
}

bool isRolleTheoremSatisfied(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c)
{
    // Rolle's theorem:
    // Let f be a function such that:
    // (i) it is continuous on the closed interval [a, b]
    // (ii) it is differentiable on the open interval (a, b)
    // (iii) f(a) = 0 and f(b) = 0
    // Then there is a number c in the open interval (a, b) such that f'(c) = 0

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, a);
    Term fa(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, b);
    Term fb(substitution.performSubstitutionTo(term));

    bool result;
    if(fa.isConstant() && fb.isConstant()
            && AlbaNumber(0U) == fa.getConstantValueConstReference()
            && AlbaNumber(0U) == fb.getConstantValueConstReference())
    {
        AlbaNumberIntervals continuityDomainIntervals(getContinuityDomain(term).getAcceptedIntervals());
        AlbaNumberIntervals differentiabilityDomainIntervals(getDifferentiabilityDomain(term).getAcceptedIntervals());
        AlbaNumberInterval abCloseInterval(createCloseEndpoint(a), createCloseEndpoint(b));
        AlbaNumberInterval abOpenInterval(createOpenEndpoint(a), createOpenEndpoint(b));

        if(isIntervalInsideTheIntervals(continuityDomainIntervals, abCloseInterval)
                && isIntervalInsideTheIntervals(differentiabilityDomainIntervals, abOpenInterval))
        {
            Differentiation differentiation(variableName);
            Term firstDerivativeTerm(differentiation.differentiate(term));
            substitution.putVariableWithValue(variableName, c);
            Term fPrimeC(substitution.performSubstitutionTo(firstDerivativeTerm));
            result = fPrimeC.isConstant() && AlbaNumber(0U) == fPrimeC.getConstantValueConstReference();
        }
    }
    return result;
}

AlbaNumbers getInputValuesInIntervalWithSameAsMeanOfInterval(
        Term const& term,
        std::string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    // Mean-Value theorem:
    // Let f be a function such that:
    // (i) it is continuous on the closed interval [a, b]
    // (ii) it is differentiable on the open interval (a, b)
    // (iii) f(a) = 0 and f(b) = 0
    // Then there is a number c in the open interval (a, b) such that f'(c) = (f(b)-f(a))/(b-a)

    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, a);
    Term fa(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, b);
    Term fb(substitution.performSubstitutionTo(term));
    AlbaNumbers result;
    if(fa.isConstant() && fb.isConstant())
    {
        AlbaNumber mean = (fb.getConstantValueConstReference()-fa.getConstantValueConstReference())/(b-a);
        Differentiation differentiation(variableName);
        Term firstDerivativeTerm(differentiation.differentiate(term));
        Equation derivativeEqualsMeanEquation(firstDerivativeTerm, "=", Term(mean));
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsMeanEquation));
        AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
        for(AlbaNumber const& acceptedValue : acceptedValues)
        {
            AlbaNumberInterval abOpenInterval(createOpenEndpoint(a), createOpenEndpoint(b));
            if(abOpenInterval.isValueInsideTheInterval(acceptedValue))
            {
                result.emplace_back(acceptedValue);
            }
        }
    }
    return result;
}

Extremum getAbsoluteExtremumBasedOnRelativeExtremaOnInterval(
        Extrema const& relativeExtrema,
        AlbaNumberInterval const& interval)
{
    // Let the function f be continuous on the interval I containing the number c.
    // If f(c) is a relative extremum of f on I and c is the ONLY in I for which f has a relative extermum,
    // then f(c) is an absolute extremum of f on I. Furthermore,
    // (i) if f(c) is relative maximum value of f on I, then f(c) is an absolute maximum value of f on I.
    // (ii) if f(c) is relative minimum value of f on I, then f(c) is an absolute minimum value of f on I.

    unsigned int numberOfExtremaFoundInInterval(0U);
    Extremum result;
    Extremum extremumInInterval;
    for(Extremum const& extremum : relativeExtrema)
    {
        if(interval.isValueInsideTheInterval(extremum.inputOutputValues.first))
        {
            extremumInInterval = extremum;
            numberOfExtremaFoundInInterval++;
            if(numberOfExtremaFoundInInterval > 1)
            {
                break;
            }
        }
    }
    if(numberOfExtremaFoundInInterval == 1) // if its the only extrema in interval then its absolute
    {
        result = extremumInInterval;
    }
    return result;
}

AlbaNumbers getCriticalNumbers(
        Term const& term,
        string const& variableName)
{
    // If c is a number in the domain of the function f, and if either f'(c) = 0 of f'(c) does not exist,
    // then c is called a critical number of f.

    Differentiation differentiation(variableName);
    Term firstDerivative(differentiation.differentiate(term));
    Equation derivativeEqualsZeroEquation(firstDerivative, "=", Term(Constant(0)));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsZeroEquation));
    AlbaNumbers result;
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    result.reserve(acceptedValues.size() + rejectedValues.size());
    copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(result));
    copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(result));
    return result;
}

AlbaNumbers getInputValuesAtPointsOfInflection(
        Term const& term,
        string const& variableName)
{
    Differentiation differentiation(variableName);
    Term secondDerivative(differentiation.differentiateMultipleTimes(term, 2));
    AlbaNumbers result;
    if(!secondDerivative.isConstant())
    {
        Equation derivativeEqualsZeroEquation(secondDerivative, "=", Term(Constant(0)));
        OneEquationOneVariableEqualitySolver solver;
        SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(derivativeEqualsZeroEquation));
        AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
        AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
        result.reserve(acceptedValues.size() + rejectedValues.size());
        copy(acceptedValues.cbegin(), acceptedValues.cend(), back_inserter(result));
        copy(rejectedValues.cbegin(), rejectedValues.cend(), back_inserter(result));
    }
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
                    result.minimumInputOutputValues.first = valueToCheck;
                    result.minimumInputOutputValues.second = evaluatedValue;
                    result.maximumInputOutputValues.first = valueToCheck;
                    result.maximumInputOutputValues.second = evaluatedValue;
                    isFirst = false;
                }
                else if(result.minimumInputOutputValues.second > evaluatedValue)
                {
                    result.minimumInputOutputValues.first = valueToCheck;
                    result.minimumInputOutputValues.second = evaluatedValue;
                }
                else if(result.maximumInputOutputValues.second < evaluatedValue)
                {
                    result.maximumInputOutputValues.first = valueToCheck;
                    result.maximumInputOutputValues.second = evaluatedValue;
                }
            }
        }
    }
    return result;
}

Extrema getRelativeExtrema(
        Term const& term,
        string const& variableName)
{
    //Let c be a critical number of a function f at which f'(c) = 0, and let f exist for all values of x in some open interval containing c.
    // If f''(c) exists and :
    // (i) if f''(c) < 0, then f has a relative maximum value at c.
    // (ii) if f''(c) > 0, then f has a relative minimum value at c.

    Differentiation differentiation(variableName);
    Term firstDerivative(differentiation.differentiate(term));
    Term secondDerivative(differentiation.differentiateMultipleTimes(term, 2U));
    Equation firstDerivativeEqualsZeroEquation(firstDerivative, "=", Term(Constant(0)));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(firstDerivativeEqualsZeroEquation));
    AlbaNumbers const& valuesWhenFirstDerivativeIsZero(solutionSet.getAcceptedValues());
    Extrema result;
    for(AlbaNumber const& valueWhenFirstDerivativeIsZero : valuesWhenFirstDerivativeIsZero)
    {
        SubstitutionOfVariablesToValues substitution({{variableName, valueWhenFirstDerivativeIsZero}});
        Term secondDerivativeTermAtCriticalValue(substitution.performSubstitutionTo(secondDerivative));
        Term evaluatedTerm(substitution.performSubstitutionTo(term));
        if(secondDerivativeTermAtCriticalValue.isConstant() && evaluatedTerm.isConstant())
        {
            AlbaNumber secondDerivativeValueAtCriticalValue(secondDerivativeTermAtCriticalValue.getConstantValueConstReference());
            if(secondDerivativeValueAtCriticalValue.isAFiniteValue())
            {
                if(secondDerivativeValueAtCriticalValue < 0)
                {
                    result.emplace_back(Extremum{ExtremumType::Maximum, {valueWhenFirstDerivativeIsZero, evaluatedTerm.getConstantValueConstReference()}});
                }
                else if(secondDerivativeValueAtCriticalValue > 0)
                {
                    result.emplace_back(Extremum{ExtremumType::Minimum, {valueWhenFirstDerivativeIsZero, evaluatedTerm.getConstantValueConstReference()}});
                }
            }
        }
    }
    return result;
}



namespace
{

void putArbitiaryValuesFromInterval(
        AlbaNumbers & arbitiaryValues,
        AlbaNumberInterval const& interval)
{
    AlbaNumberIntervalEndpoint lowEndpoint(interval.getLowerEndpoint());
    AlbaNumberIntervalEndpoint highEndpoint(interval.getHigherEndpoint());
    AlbaNumber lowValue(convertIfInfinityToNearestFiniteValue(lowEndpoint.getValue()));
    AlbaNumber highValue(convertIfInfinityToNearestFiniteValue(highEndpoint.getValue()));
    if(lowEndpoint.isClose())
    {
        arbitiaryValues.emplace_back(lowValue);
    }
    if(highEndpoint.isClose())
    {
        arbitiaryValues.emplace_back(highValue);
    }
    for(unsigned int level=0; level<5; level++)
    {
        AlbaNumber midpoint = (lowValue+highValue)/2;
        lowValue = (lowValue + midpoint)/2;
        highValue = (highValue + midpoint)/2;
        arbitiaryValues.emplace_back(lowValue);
        arbitiaryValues.emplace_back(midpoint);
        arbitiaryValues.emplace_back(highValue);
    }
}

void putArbitiaryValuesBasedFromDomainOfTerm(
        AlbaNumbers & arbitiaryValues,
        Term const& term)
{
    SolutionSet domainSolutionSet = calculateDomainForTermWithOneVariable(term);
    AlbaNumberIntervals domains(domainSolutionSet.getAcceptedIntervals());
    for(AlbaNumberInterval const domain : domains)
    {
        putArbitiaryValuesFromInterval(arbitiaryValues, domain);
    }
}

}

}

}
