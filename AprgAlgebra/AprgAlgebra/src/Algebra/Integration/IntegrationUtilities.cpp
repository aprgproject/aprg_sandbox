#include "IntegrationUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Summation/Summation.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace std;
namespace alba
{
namespace algebra
{

bool isTheSecondFundamentalTheoremOfCalculusTrue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    // The second fundamental theorem of calculus
    // Let the function f be continuous on the closed interval [a, b] and let the derivative of g be equal to f for all x in [a, b].
    // Then the definite integral of f from a to b is equal of g(b)- g(a)

    Differentiation differentiation(variableName);
    Integration integration(variableName);
    Term g(integration.integrate(term));
    Term gPrime(differentiation.differentiate(g));
    Term simplifiedTerm(term);
    simplifiedTerm.simplify();
    bool isGPrimeEqualToF = gPrime == simplifiedTerm;
    bool isDefiniteIntegralEqualToDifference = integration.integrateWithDefiniteValues(term, a, b)
            == evaluateAndGetDifference(g, variableName, a, b);
    return isGPrimeEqualToF && isDefiniteIntegralEqualToDifference;
}
bool isTheIntegralDefinitionForFiniteCalculusIsTrue(
        Term const& term,
        string const& variableName,        AlbaNumber const& a,
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
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    // Mean-Value theorem for integrals:
    // If the function f is continuous on the closed interval [a, b],
    // there exists a number "average" in [a, b] such that:
    // The definite integral in [a, b] = f("average") * (b-a)

    Equation meanValueTheoremEquation(term, "=", getAverageValueInBetweenTwoValues(term, variableName, lowerValueInInterval, higherValueInInterval));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(meanValueTheoremEquation));
    AlbaNumberInterval openInterval(createOpenEndpoint(lowerValueInInterval), createOpenEndpoint(higherValueInInterval));
    return getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), openInterval);
}

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    Integration integration(variableName);
    return integration.integrateWithDefiniteValues(term, lowerValueInInterval, higherValueInInterval)
            / Term(higherValueInInterval-lowerValueInInterval);
}

Term evaluateAndGetDifference(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    Term result(evaluate(term, variableName, Term(higherValueInInterval))
                - evaluate(term, variableName, Term(lowerValueInInterval)));
    result.simplify();
    return result;
}

Term evaluateAndGetDifference(
        Term const& term,
        string const& variableName,
        Term const& lowerValueTerm,
        Term const& higherValueTerm)
{
    Term result(evaluate(term, variableName, higherValueTerm)
                - evaluate(term, variableName, lowerValueTerm));
    result.simplify();
    return result;
}

Term evaluate(
        Term const& term,
        std::string const& variableName,
        Term const& value)
{
    Term result;
    if(isTheValue(value, AlbaNumber(AlbaNumber::Value::PositiveInfinity)))
    {
        result = getLimit(term, variableName, AlbaNumber(AlbaNumber::Value::PositiveInfinity));
    }
    else if(isTheValue(value, AlbaNumber(AlbaNumber::Value::NegativeInfinity)))
    {
        result = getLimit(term, variableName, AlbaNumber(AlbaNumber::Value::NegativeInfinity));
    }
    else
    {
        SubstitutionOfVariablesToTerms substitution({{variableName, value}});
        result = substitution.performSubstitutionTo(term);
    }
    return result;
}

Term getAreaUnderACurveUsingReimannSums(
        Term const& term,
        string const& variableName,        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    AlbaNumber deltaOfValues(higherValueInInterval-lowerValueInInterval);    Term inputForHeight(Polynomial{Monomial(lowerValueInInterval, {}), Monomial(deltaOfValues, {{"n", -1}, {variableName, 1}})});
    SubstitutionOfVariablesToTerms substitution({{variableName, inputForHeight}});
    Term heightOfARectangle(substitution.performSubstitutionTo(term));
    Term widthOfARectangle(Monomial(deltaOfValues, {{"n", -1}}));
    Term areaOfARectangle(heightOfARectangle * widthOfARectangle);
    Summation summation(areaOfARectangle, variableName);
    Term sumOfAreaOfAllRectangles(summation.getSum(Term(1), Term("n")));
    LimitsAtInfinity limits(sumOfAreaOfAllRectangles, "n");
    return limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity); // Let number of rectangles approach infinity
}

LowerAndHigherValues getApproximateValuesForDefiniteIntegral(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerValueInInterval,
        AlbaNumber const& higherValueInInterval)
{
    AlbaNumberInterval closedInterval(createCloseEndpoint(lowerValueInInterval), createCloseEndpoint(higherValueInInterval));
    MinimumAndMaximum minMaxValues(getMinimumAndMaximumAtClosedInterval(term, variableName, closedInterval));
    AlbaNumber delta(higherValueInInterval-lowerValueInInterval);
    LowerAndHigherValues result;
    result.higherValue = minMaxValues.maximumInputOutputValues.second * delta;
    result.lowerValue = minMaxValues.minimumInputOutputValues.second * delta;
    return result;
}

}

}
