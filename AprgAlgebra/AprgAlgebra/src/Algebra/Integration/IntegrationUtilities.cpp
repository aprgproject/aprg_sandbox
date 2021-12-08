#include "IntegrationUtilities.hpp"

#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Extrema/ExtremaUtilities.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
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
    bool isDefiniteIntegralEqualToDifference = integration.integrateAtDefiniteValues(term, a, b)
            == evaluateValuesAndGetDifference(g, variableName, a, b);
    return isGPrimeEqualToF && isDefiniteIntegralEqualToDifference;
}

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
    return integration.integrateAtDefiniteValues(term, a, b) == summation.getSum(Term(a), Term(b-1));
}

bool isAreaUnderTheCurveEqualToDefiniteIntegral(
        Term const& term,
        string const& variableName,
        AlbaNumber const& a,
        AlbaNumber const& b)
{
    Integration integration(variableName);
    return integration.integrateAtDefiniteValues(term, a, b)
            == getAreaUnderACurveUsingReimannSums(term, variableName, a, b);
}

AlbaNumbers getInputForAverageValueInBetweenTwoValues(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval)
{
    // Mean-Value theorem for integrals:
    // If the function f is continuous on the closed interval [a, b],
    // there exists a number "average" in [a, b] such that:
    // The definite integral in [a, b] = f("average") * (b-a)

    Equation meanValueTheoremEquation(term, "=", getAverageValueInBetweenTwoValues(term, {variableName, lowerEndInInterval, higherEndInInterval}));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(meanValueTheoremEquation));
    AlbaNumberInterval openInterval(createOpenEndpoint(lowerEndInInterval), createOpenEndpoint(higherEndInInterval));
    return getNumbersInsideTheInterval(solutionSet.getAcceptedValues(), openInterval);
}

Term getAverageValueInBetweenTwoValues(
        Term const& term,
        DetailsForDefiniteIntegralWithValues const& integralDetails)
{
    Integration integration(integralDetails.variableName);
    return integration.integrateAtDefiniteValues(term, integralDetails.lowerEnd, integralDetails.higherEnd)
            / Term(integralDetails.higherEnd-integralDetails.lowerEnd);
}

Term evaluateValuesAndGetDifference(
        Term const& term,
        string const& variableName,
        AlbaNumber const& lowerEnd,
        AlbaNumber const& higherEnd)
{
    Term result(evaluate(term, variableName, Term(higherEnd))
                - evaluate(term, variableName, Term(lowerEnd)));
    result.simplify();
    return result;
}

Term evaluateTermsAndGetDifference(
        Term const& term,
        string const& variableName,
        Term const& lowerEnd,
        Term const& higherEnd)
{
    Term result(evaluate(term, variableName, higherEnd)
                - evaluate(term, variableName, lowerEnd));
    result.simplify();
    return result;
}

Term evaluate(
        Term const& term,
        string const& variableName,
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
        string const& variableName,
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval)
{
    AlbaNumber deltaOfValues(higherEndInInterval-lowerEndInInterval);
    Term inputForHeight(Polynomial{Monomial(lowerEndInInterval, {}), Monomial(deltaOfValues, {{"n", -1}, {variableName, 1}})});
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
        AlbaNumber const& lowerEndInInterval,
        AlbaNumber const& higherEndInInterval)
{
    AlbaNumberInterval closedInterval(createCloseEndpoint(lowerEndInInterval), createCloseEndpoint(higherEndInInterval));
    MinimumAndMaximum minMaxValues(getMinimumAndMaximumAtClosedInterval(term, variableName, closedInterval));
    AlbaNumber delta(higherEndInInterval-lowerEndInInterval);
    LowerAndHigherValues result;
    result.higherValue = minMaxValues.maximumInputOutputValues.second * delta;
    result.lowerValue = minMaxValues.minimumInputOutputValues.second * delta;
    return result;
}

}

}
