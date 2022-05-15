#include "SeriesUtilities.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

bool isAxiomOfCompletenessTrue(
        SeriesBasedOnFormula const& series)
{
    // Axiom of completeness
    // Every non empty set of real numbers that has a lower bound has a greatest lower bound.
    // Also, every non empty set of real numbers that has an upper bound has a least upper bound.

    AlbaNumberOptional greatestLowerBound(series.getGreatestLowerBound());
    AlbaNumberOptional leastUpperBound(series.getLeastUpperBound());
    return (greatestLowerBound.hasContent() && leastUpperBound.hasContent())
            || (!greatestLowerBound.hasContent() && !leastUpperBound.hasContent());
}

bool isBoundedMonotonicSeriesConvergent(
        SeriesBasedOnFormula const& series)
{
    return (series.isBounded() && series.isMonotonic()) == series.isConvergent();
}

bool isConvergentMonotonicSeriesBounded(
        SeriesBasedOnFormula const& series)
{
    return (series.isConvergent() && series.isMonotonic()) == series.isBounded();
}

bool isConvergentUsingComparisonTest(
        SeriesBasedOnSummation const& seriesToCheck,
        SeriesBasedOnSummation const& convergentSeries,
        unsigned int const numberOfIndexesToTest)
{
    bool result(false);
    if(convergentSeries.isConvergent())
    {
        bool areAllValuesSatisfied(true);
        for(int i=0; i<static_cast<int>(numberOfIndexesToTest); i++)
        {
            Term termToCheck(seriesToCheck.getTermValueAtIndex(i));
            Term convergentTerm(convergentSeries.getTermValueAtIndex(i));
            if(termToCheck.isConstant() && convergentTerm.isConstant())
            {
                areAllValuesSatisfied
                        = (termToCheck.getConstantValueConstReference() <= convergentTerm.getConstantValueConstReference());
                if(!areAllValuesSatisfied)
                {
                    break;
                }
            }
        }
        result = areAllValuesSatisfied;
    }
    return result;
}

bool isDivergentUsingComparisonTest(
        SeriesBasedOnSummation const& seriesToCheck,
        SeriesBasedOnSummation const& divergentSeries,
        unsigned int const numberOfIndexesToTest)
{
    bool result(false);
    if(!divergentSeries.isConvergent())
    {
        bool areAllValuesSatisfied(true);
        for(int i=0; i<static_cast<int>(numberOfIndexesToTest); i++)
        {
            Term termToCheck(seriesToCheck.getTermValueAtIndex(i));
            Term divergentTerm(divergentSeries.getTermValueAtIndex(i));
            if(termToCheck.isConstant() &&  divergentTerm.isConstant())
            {
                areAllValuesSatisfied
                        = (termToCheck.getConstantValueConstReference() >=  divergentTerm.getConstantValueConstReference());
                if(!areAllValuesSatisfied)
                {
                    break;
                }
            }
        }
        result = areAllValuesSatisfied;
    }
    return result;
}

void performLimitComparisonTest(
        bool & isConvergent,
        bool & isDivergent,
        SeriesBasedOnSummation const& series1,
        SeriesBasedOnSummation const& series2,
        string const& variableName)
{
    Term formula1(series1.getFormulaForEachTermInSummation());
    Term formula2(series2.getFormulaForEachTermInSummation());
    Term termForLimitChecking(formula1/formula2);
    Term limit(getLimit(termForLimitChecking, variableName, AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    if(isTheValue(limit, 0))
    {
        if(series2.isConvergent())
        {
            isConvergent = true;
        }
    }
    else if(isTheValue(limit, AlbaNumber(AlbaNumber::Value::PositiveInfinity)))
    {
        if(!series2.isConvergent())
        {
            isDivergent = true;
        }
    }
}

void performIntegralTest(
        bool & isConvergent,
        bool & isDivergent,
        SeriesBasedOnSummation const& series,
        string const& variableName)
{
    Integration integration(variableName);
    Term integratedTerm(integration.integrateAtDefiniteTerms(
              series.getFormulaForEachTermInSummation(), 1, AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    if(isTheValue(integratedTerm, AlbaNumber(AlbaNumber::Value::PositiveInfinity)))
    {
        isDivergent = true;
    }
    else if(!isNan(integratedTerm))
    {
        isConvergent = true;
    }}

void performRatioTest(
        bool & isConvergent,        bool & isDivergent,
        SeriesBasedOnSummation const& series,
        string const& variableName)
{
    Term limitTerm(getLimitForRatioTest(series, variableName));
    if(limitTerm.isConstant())
    {
        AlbaNumber limitValue(limitTerm.getConstantValueConstReference());
        if(limitValue < 1)
        {
            isConvergent = true;
        }
        else if(limitValue > 1)
        {
            isDivergent = true;
        }
    }
}

void performRootTest(
        bool & isConvergent,
        bool & isDivergent,
        SeriesBasedOnSummation const& series,
        string const& variableName)
{
    Term formulaForEachTerm(series.getFormulaForEachTermInSummation());
    TermsOverTerms termsOverTerms(createTermsOverTermsFromTerm(formulaForEachTerm));
    TermsRaiseToTerms termsRaiseToTerms(termsOverTerms.getTermsRaiseToTerms());
    termsRaiseToTerms.multiplyToExponents(Monomial(1, {{variableName, -1}}));
    Term termForLimit(termsRaiseToTerms.getCombinedTerm());
    Term limitTerm(getLimit(termForLimit, variableName, AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
    if(limitTerm.isConstant())
    {
        AlbaNumber limitValue(limitTerm.getConstantValueConstReference());
        if(limitValue < 1)
        {
            isConvergent = true;
        }
        else if(limitValue > 1)
        {
            isDivergent = true;
        }
    }
}

Term getLimitForRatioTest(
        SeriesBasedOnSummation const& series,
        string const& variableName)
{
    SubstitutionOfVariablesToTerms substitution
    {{variableName, Polynomial{Monomial(1, {{variableName, 1}}), Monomial(1, {})}}};
    Term formulaForEachTerm(series.getFormulaForEachTermInSummation());
    Term formulaForEachTermWithPlusOne(substitution.performSubstitutionTo(formulaForEachTerm));
    Term termForLimit(convertPositiveTermIfNegative(formulaForEachTermWithPlusOne) / convertPositiveTermIfNegative(formulaForEachTerm));
    return getLimit(termForLimit, variableName, AlbaNumber(AlbaNumber::Value::PositiveInfinity));
}

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(
        Term const& firstTerm,
        Term const& lastTerm,
        Term const& count)
{
    return (firstTerm + lastTerm) * count / 2;
}

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        Term const& firstValue,
        Term const& commonMultiplier,
        int const count)
{
    return firstValue * (1-(commonMultiplier^count)) / (1-commonMultiplier);
}

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        Term const& firstValue,
        Term const& commonMultiplier)
{
    return firstValue/(1 - commonMultiplier);
}

PowerSeries getEToTheXPowerSeries()
{
    Term formula(convertExpressionToSimplestTerm(createExpressionIfPossible({1, "/", factorial(n)})));
    return PowerSeries(formula, n, x, 0);
}

}

}
