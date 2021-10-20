#include "Summation.hpp"

#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

Summation::Summation(
        Term const& termToSum,
        string const& variableToSubstitute)
    : m_termToSum(termToSum)
    , m_variableToSubstitute(variableToSubstitute)
    , m_summationModel(getSummationModel())
{}

Term Summation::getSummationModelWithKnownConstant(
        AlbaNumber const& startNumber) const
{
    SubstitutionOfVariablesToValues substitution({{m_variableToSubstitute, startNumber}});
    Term firstTerm(substitution.performSubstitutionTo(m_termToSum));
    substitution.putVariableWithValue(m_variableToSubstitute, startNumber);
    Term summationValueFromModel(substitution.performSubstitutionTo(m_summationModel));
    Term difference = firstTerm - summationValueFromModel;
    Term result(m_summationModel + difference);
    return result;
}

Term Summation::getSummationModelWithUnknownConstant() const
{
    return m_summationModel + Term(C);
}

Term Summation::getSum(
        Term const& start,
        Term const& end) const
{
    Term result;
    bool isStartAFiniteConstant = start.isConstant() && start.getConstantValueConstReference().isAFiniteValue();
    bool isEndAFiniteConstant = end.isConstant() && end.getConstantValueConstReference().isAFiniteValue();
    if(isStartAFiniteConstant && isEndAFiniteConstant)
    {
        calculateSumFromANumberToANumber(result, start.getConstantValueConstReference(), end.getConstantValueConstReference());
    }
    else if(isStartAFiniteConstant)
    {
        calculateSumStartingFromANumber(result, start.getConstantValueConstReference(), end);
    }
    else
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
    return result;
}

void Summation::calculateSumFromANumberToANumber(
        Term & result,
        AlbaNumber const& startNumber,
        AlbaNumber const& endNumber) const
{
    if(startNumber.isIntegerType()
            && endNumber.isIntegerType()
            && startNumber <= endNumber)
    {
        if(isNotANumber(m_summationModel))
        {
            calculateSumUsingEachTerm(result, startNumber, endNumber);
        }
        else
        {
            calculateSumUsingModel(result, startNumber, endNumber);
        }
    }
    else
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

void Summation::calculateSumStartingFromANumber(
        Term & result,
        AlbaNumber const& startNumber,
        Term const& end) const
{
    if(startNumber.isIntegerType())
    {
        Term summationModelWithConstant(getSummationModelWithKnownConstant(startNumber));

        if(end.isConstant() && end.getConstantValueConstReference().isPositiveInfinity())
        {
            LimitsAtInfinity limits(summationModelWithConstant, m_variableToSubstitute);
            result = limits.getValueAtInfinity(AlbaNumber::Value::PositiveInfinity);
        }
        else
        {
            SubstitutionOfVariablesToTerms substitution({{m_variableToSubstitute, end}});
            result = substitution.performSubstitutionTo(summationModelWithConstant);
        }
    }
    else
    {
        result = Term(AlbaNumber(AlbaNumber::Value::NotANumber));
    }
}

void Summation::calculateSumUsingEachTerm(
        Term& result,
        AlbaNumber const& startNumber,
        AlbaNumber const& endNumber) const
{
    long long start(startNumber.getInteger());
    long long end(endNumber.getInteger());
    Term sum;
    bool isFirst(true);
    SubstitutionOfVariablesToValues substitution;
    for(long long i(start); i<=end; i++)
    {
        substitution.putVariableWithValue(m_variableToSubstitute, i);
        Term termWithValue(substitution.performSubstitutionTo(m_termToSum));
        if(isFirst)
        {
            sum = termWithValue;
            isFirst=false;
        }
        else
        {
            sum = sum + termWithValue;
        }
    }
    result = sum;
}

void Summation::calculateSumUsingModel(
        Term & result,
        AlbaNumber const& startNumber,
        AlbaNumber const& endNumber) const
{
    Term summationModelWithConstant(getSummationModelWithKnownConstant(startNumber));
    SubstitutionOfVariablesToValues substitution({{m_variableToSubstitute, endNumber}});
    result = substitution.performSubstitutionTo(summationModelWithConstant);
}

Term Summation::getSummationModel() const
{
    IntegrationForFiniteCalculus integration(m_variableToSubstitute);
    // Put plus one because finite calculus terms are summation up to n-1.
    Term variablePlusOne(Polynomial{Monomial(1, {{m_variableToSubstitute, 1}}), Monomial(1, {})});
    SubstitutionOfVariablesToTerms substitution({{m_variableToSubstitute, variablePlusOne}});
    return substitution.performSubstitutionTo(integration.integrate(m_termToSum));
}


}

}
