#include "IntegrationUtilities.hpp"

#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    // The fundamental theorem of finite calculus:

    // The discrete definite integral from a to b is equal to
    // The summation of terms from a to b-1.
    IntegrationForFiniteCalculus integration(variableName);
    Summation summation(term, variableName);
    return integration.integrateWithDefiniteValues(term, a, b) == summation.getSum(Term(a), Term(b-1));
}

bool isAreaUnderTheCurveEqualToDefiniteIntegral(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    Integration integration(variableName);
    return integration.integrateWithDefiniteValues(term, a, b)
            == getAreaUnderACurveUsingReimannSums(term, variableName, a, b);
}

AlbaNumbers getInputForAverageValueInBetweenTwoValues(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    // Mean-Value theorem for integrals:
    // If the function f is continuous on the closed interval [a, b],
    // there exists a number "average" in [a, b] such that:
    // The definite integral in [a, b] = f("average") * (b-a)

    Equation meanValueTheoremEquation(term, "=", getAverageValueInBetweenTwoValues(term, variableName, lowerValue, higherValue));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(meanValueTheoremEquation));
    AlbaNumberInterval openInterval(createOpenEndpoint(lowerValue), createOpenEndpoint(higherValue));
    return getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), openInterval);
}

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    Integration integration(variableName);
    return integration.integrateWithDefiniteValues(term, lowerValue, higherValue)
            / Term(higherValue-lowerValue);
}

Term substituteValuesAndGetDifference(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    SubstitutionOfVariablesToValues substitution({{variableName, lowerValue}});
    Term integralWithLowerValue(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, higherValue);
    Term integralWithHigherValue(substitution.performSubstitutionTo(term));
    return integralWithHigherValue-integralWithLowerValue;
}

Term getAreaUnderACurveUsingReimannSums(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    AlbaNumber deltaOfValues(higherValue-lowerValue);
    Term inputForHeight(Polynomial{Monomial(lowerValue, {}), Monomial(deltaOfValues, {{"n", -1}, {variableName, 1}})});
    SubstitutionOfVariablesToTerms substitution({{variableName, inputForHeight}});
    Term heightOfARectangle(substitution.performSubstitutionTo(term));
    Term widthOfARectangle(Monomial(deltaOfValues, {{"n", -1}}));
    Term areaOfARectangle(heightOfARectangle * widthOfARectangle);
    Summation summation(areaOfARectangle, variableName);
    Term sumOfAreaOfAllRectangles(summation.getSum(Term(1), Term("n")));
    LimitsAtInfinity limits(sumOfAreaOfAllRectangles, "n");
    return limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity); // Let number of rectangles approach infinity
}

LowerAndHigherValues getApproximateValueForDefiniteIntegral(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValue,
        AlbaNumber const& higherValue)
{
    AlbaNumberInterval closedInterval(createCloseEndpoint(lowerValue), createCloseEndpoint(higherValue));
    MinimumAndMaximum minMaxValues(getMinimumAndMaximumAtClosedInterval(term, variableName, closedInterval));
    AlbaNumber delta(higherValue-lowerValue);
    LowerAndHigherValues result;
    result.higherValue = minMaxValues.maximumInputOutputValues.second * delta;
    result.lowerValue = minMaxValues.minimumInputOutputValues.second * delta;
    return result;
}

}

}
