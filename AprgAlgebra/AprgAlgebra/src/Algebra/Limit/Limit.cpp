#include "Limit.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/RetrieveHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Simplification;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

constexpr double COMPARISON_TOLERANCE_FOR_LIMIT_ITERATION=1E-15;
constexpr double COMPARISON_TOLERANCE_FOR_LIMIT_CHECKING=1E-5;
constexpr unsigned int MAX_NUMBER_OF_ITERATIONS=100;
constexpr double POSITIVE_DELTA_FOR_INITIAL_VALUE=1E-3;

}

bool isAlmostEqualForLimitIteration(AlbaNumber const& value1, AlbaNumber const& value2)
{
    return isAlmostEqual(value1.getDouble(), value2.getDouble(), COMPARISON_TOLERANCE_FOR_LIMIT_ITERATION);
}

bool isAlmostEqualForLimitChecking(AlbaNumber const& value1, AlbaNumber const& value2)
{
    return isAlmostEqual(value1.getDouble(), value2.getDouble(), COMPARISON_TOLERANCE_FOR_LIMIT_CHECKING);
}

bool hasVerticalAsymptoteAtValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    return getLimitAtAValueInThePositiveSide(term, variableName, valueToApproach).isPositiveOrNegativeInfinity()
            || getLimitAtAValueInTheNegativeSide(term, variableName, valueToApproach).isPositiveOrNegativeInfinity();
}

bool hasHorizontalAsymptoteAtValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    bool result(false);
    Term limitAtPositiveInfinity(getLimitAtInfinity(term, variableName, AlbaNumber::Value::PositiveInfinity));
    Term limitAtNegativeInfinity(getLimitAtInfinity(term, variableName, AlbaNumber::Value::NegativeInfinity));
    if(limitAtPositiveInfinity.isConstant() && limitAtNegativeInfinity.isConstant())
    {
        result = limitAtPositiveInfinity.getConstantValueConstReference() == valueToApproach
                || limitAtNegativeInfinity.getConstantValueConstReference() == valueToApproach;
    }
    return result;
}

bool isSqueezeTheoremSatisfied(
        Term const& alwaysLowerTermAtInterval,
        Term const& termInBetweenAtInterval,
        Term const& alwaysHigherTermAtInterval,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    // Theorem: Suppose that the functions f, g, and h are defined on some open interval I containing A except
    // possibly A itself, and that f(x) <= g(x) <= h(x) for all x in I for which x != A. Also that the limit for
    // f(x) as it approaches A and limit for h(x) as it approaches A, both exists and are both equal to L
    // Then, the limit of g(x) exists and equal to L as well.

    bool result(false);
    Term limitAtLower(simplifyAndGetLimitAtAValue(alwaysLowerTermAtInterval, variableName, valueToApproach, LimitAtAValueApproachType::BothSides));
    Term limitAtTermInBetween(simplifyAndGetLimitAtAValue(termInBetweenAtInterval, variableName, valueToApproach, LimitAtAValueApproachType::BothSides));
    Term limitAtHigher(simplifyAndGetLimitAtAValue(alwaysHigherTermAtInterval, variableName, valueToApproach, LimitAtAValueApproachType::BothSides));

    if(limitAtLower == limitAtHigher)
    {
        //double check if limit really exists
        result = limitAtTermInBetween == limitAtLower;
    }
    return result;
}

AlbaNumber getLimitAtAValueByApproachType(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType)
{
    AlbaNumber result;
    if(LimitAtAValueApproachType::BothSides == limitApproachType)
    {
        result = getLimitAtAValueInBothSides(term, variableName, valueToApproach);
    }
    else if(LimitAtAValueApproachType::PositiveSide == limitApproachType)
    {
        result = getLimitAtAValueInThePositiveSide(term, variableName, valueToApproach);
    }
    else if(LimitAtAValueApproachType::NegativeSide == limitApproachType)
    {
        result = getLimitAtAValueInTheNegativeSide(term, variableName, valueToApproach);
    }
    return result;
}

AlbaNumber getLimitAtAValueInBothSides(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    AlbaNumber result(AlbaNumber::Value::NotANumber);
    AlbaNumber limitPositiveSide(getLimitAtAValueInThePositiveSide(term, variableName, valueToApproach));
    AlbaNumber limitNegativeSide(getLimitAtAValueInTheNegativeSide(term, variableName, valueToApproach));
    if(isAlmostEqualForLimitChecking(limitPositiveSide, limitNegativeSide)) //limit only exists if both sides are equal  (Calculus Theorem)
    {
        result = getAverageForAlbaNumber(limitPositiveSide, limitNegativeSide);
    }
    return result;
}

AlbaNumber getLimitAtAValueInThePositiveSide(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    return getLimitAtAValueByIterationAndLinearInterpolation(
                term,
                variableName,
                valueToApproach,
                valueToApproach + POSITIVE_DELTA_FOR_INITIAL_VALUE,
                MAX_NUMBER_OF_ITERATIONS);
}

AlbaNumber getLimitAtAValueInTheNegativeSide(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach)
{
    return getLimitAtAValueByIterationAndLinearInterpolation(
                term,
                variableName,
                valueToApproach,
                valueToApproach - POSITIVE_DELTA_FOR_INITIAL_VALUE,
                MAX_NUMBER_OF_ITERATIONS);
}

AlbaNumber getLimitAtAValueByIterationAndLinearInterpolation(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        AlbaNumber const& initialValueForIteration,
        unsigned int maxNumberOfIterations)
{
    AlbaNumber::ScopeObject scopeObject;
    scopeObject.setInThisScopeTheTolerancesToZero();

    SubstitutionOfVariablesToValues substitution;
    AlbaNumber currentInput(initialValueForIteration);
    AlbaNumber previousAcceptedInput(currentInput);
    AlbaNumber previousPreviousAcceptedInput(currentInput);
    AlbaNumber previousRejectedInput(valueToApproach);
    for(unsigned int i=0; i<maxNumberOfIterations && currentInput != previousRejectedInput; i++)
    {
        // As current currentInput approaches valueToApproach the calculation becomes inaccurate so limit value is not accurate.
        substitution.putVariableWithValue(variableName, currentInput);
        Term currentOutputTerm = substitution.performSubstitutionTo(term);
        if(currentOutputTerm.isConstant())        {
            AlbaNumber currentOutputNumber(currentOutputTerm.getConstantValueConstReference());
            if(!currentOutputNumber.isARealFiniteValue())
            {                previousRejectedInput = currentInput;
            }
            else
            {
                previousPreviousAcceptedInput = previousAcceptedInput;
                previousAcceptedInput = currentInput;
            }
            AlbaNumber newInput(getAverageForAlbaNumber(previousAcceptedInput, previousRejectedInput));
            // to investigate, print currentInput, currentOutputNumber and newInput to check how it approaches the limit value
            // this are checks to prevent inaccurate values when the values get to close
            if(isAlmostEqualForLimitIteration(newInput, valueToApproach)
                    || isAlmostEqualForLimitIteration(newInput, previousAcceptedInput))
            {
                break;
            }            currentInput = newInput;
        }
        else
        {
            break;
        }
    }
    return getLimitAtAValueUsingTrendOfValues(term, variableName, valueToApproach, previousAcceptedInput, previousPreviousAcceptedInput);
}
AlbaNumber getLimitAtAValueUsingTrendOfValues(
        Term const& term,
        string const& variableName,        AlbaNumber const& valueToApproach,
        AlbaNumber const& previousAcceptedInput,
        AlbaNumber const& previousPreviousAcceptedInput)
{
    AlbaNumber::ScopeObject scopeObject;
    scopeObject.setInThisScopeTheTolerancesToZero();

    AlbaNumber result(AlbaNumber::Value::NotANumber);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, valueToApproach);
    Term outputTermAtValueToApproach(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, previousAcceptedInput);
    Term previousAcceptedOutputTerm(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, previousPreviousAcceptedInput);
    Term previousPreviousAcceptedOutputTerm(substitution.performSubstitutionTo(term));

    if(outputTermAtValueToApproach.isConstant()
            && previousAcceptedOutputTerm.isConstant()
            && previousPreviousAcceptedOutputTerm.isConstant())
    {
        AlbaNumber outputAtValueToApproach(outputTermAtValueToApproach.getConstantValueConstReference());
        AlbaNumber previousAcceptedOutput(previousAcceptedOutputTerm.getConstantValueConstReference());
        AlbaNumber previousPreviousAcceptedOutput(previousPreviousAcceptedOutputTerm.getConstantValueConstReference());
        if(outputAtValueToApproach.isPositiveOrNegativeInfinity())
        {
            result = (previousAcceptedOutput<0) ?
                        AlbaNumber(AlbaNumber::Value::NegativeInfinity) :
                        AlbaNumber(AlbaNumber::Value::PositiveInfinity);
        }
        else
        {
            result = getValueUsingLinearInterpolation(
                        previousPreviousAcceptedInput,
                        previousAcceptedInput,
                        valueToApproach,
                        previousPreviousAcceptedOutput,
                        previousAcceptedOutput);
        }
    }
    return result;
}

AlbaNumber getValueUsingLinearInterpolation(
        AlbaNumber const& input1,
        AlbaNumber const& input2,
        AlbaNumber const& inputValue,
        AlbaNumber const& output1,
        AlbaNumber const& output2)
{
    AlbaNumber deltaInput = input2-input1;
    AlbaNumber deltaOutput = output2-output1;
    AlbaNumber deltaInputToUse = inputValue-input2;
    AlbaNumber result;
    if(deltaInput == 0)
    {
        result = AlbaNumber(AlbaNumber::Value::NotANumber);
    }
    else
    {
        result = output2 + (deltaOutput / deltaInput * deltaInputToUse);
    }
    return result;
}

Term getLimitAtAValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType)
{
    SubstitutionOfVariablesToValues substitution{{variableName, valueToApproach}};
    Term limitResult(substitution.performSubstitutionTo(term));
    if(limitResult.isConstant())
    {
        AlbaNumber limitResultNumber(limitResult.getConstantValueConstReference());
        if(!limitResultNumber.isARealFiniteValue() || hasAnyFunctions(term))
        {
            limitResult = Term(getLimitAtAValueByApproachType(term, variableName, valueToApproach, limitApproachType));
        }
    }
    return limitResult;
}

Term simplifyTermForLimit(Term const& term)
{
    SimplificationOfExpression::ConfigurationDetails limitConfigurationDetails(
                SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
    limitConfigurationDetails.shouldSimplifyToACommonDenominator = true;

    SimplificationOfExpression::ScopeObject scopeObject;
    scopeObject.setInThisScopeThisConfiguration(limitConfigurationDetails);

    Term simplifiedTerm(term);
    simplifiedTerm.simplify();

    return simplifiedTerm;
}

Term simplifyAndGetLimitAtAValue(
        Term const& term,
        string const& variableName,
        AlbaNumber const& valueToApproach,
        LimitAtAValueApproachType const limitApproachType)
{
    Term simplifiedTerm(simplifyTermForLimit(term));
    return getLimitAtAValue(simplifiedTerm, variableName, valueToApproach, limitApproachType);
}

Term getLimitAtInfinity(
        Term const& term,
        string const& variableName,
        AlbaNumber::Value const infinityValue)
{
    LimitsAtInfinity limitsAtInfinity(term, variableName);
    return limitsAtInfinity.getValueAtInfinity(infinityValue);
}

Term getObliqueAsymptote(Term const& term)
{
    // oblique asymptote definition
    // if this true: limit to positive infinity of |f(x)/g(x) - (mx+b)| = 0 for a certain mx+b
    // then y=mx+b is an oblique asymptote.
    //
    // So just divide polynomial over polynomial and get quotient if its a line
    // If denominator is not constant, then remainder can be discarded

    Term result;
    PolynomialOverPolynomialOptional popOptional(createPolynomialOverPolynomialFromTermIfPossible(term));
    if(popOptional.hasContent())
    {
        if(popOptional.getConstReference().getDenominator().getMaxDegree() > 0)
        {
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(popOptional.getReference().simplifyAndDivide());
            Polynomial const& quotient(quotientAndRemainder.quotient);
            VariableNamesRetriever retriever;
            retriever.retrieveFromPolynomial(quotient);
            VariableNamesSet const& variableNames(retriever.getSavedData());
            if(1U == variableNames.size() && AlbaNumber(1) == quotient.getMaxDegree())
            {
                result = Term(quotient);
            }
        }
    }
    return result;
}

}

}
