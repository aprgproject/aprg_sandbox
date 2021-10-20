#include "Continuity.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Retrieval/FunctionsRetriever.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

using namespace alba::algebra::DomainAndRange;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

bool isContinuousAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType)
{
    bool result(false);
    SubstitutionOfVariablesToValues substitution{{variableName, value}};
    Term subtitutedResult(substitution.performSubstitutionTo(term));
    if(subtitutedResult.isConstant())
    {
        AlbaNumber limitAtValue(getLimitAtAValueByApproachType(term, variableName, value, limitApproachType));
        AlbaNumber const& subtitutedResultValue(subtitutedResult.getConstantValueConstReference());
        result = isAlmostEqualForLimitChecking(subtitutedResultValue, limitAtValue);
    }
    return result;
}

bool isContinuousAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType,
        bool const isDifferentiableAtValue)
{
    //If a function is differentiable at X, then f is continuous at X.
    bool result(true);
    if(!isDifferentiableAtValue)
    {
        result = isContinuousAt(term, variableName, value, limitApproachType);
    }
    return result;
}

bool isIntermediateValueTheoremSatisfied(
        Term const& term,
        string const& variableName,
        AlbaNumber const& firstValue,
        AlbaNumber const& secondValue,
        AlbaNumber const& valueToTest)
{
    // Theorem: If the function f is continuous on the closed interval [v1, v2] and if f(v1) != f(v2),
    // then for any number k between f(v1) and f(v2) there exists a number v3 between v1 and v2 such that f(v3) = k

    bool result(false);
    SubstitutionOfVariablesToValues substitution;
    substitution.putVariableWithValue(variableName, firstValue);
    Term outputOfFirst(substitution.performSubstitutionTo(term));
    substitution.putVariableWithValue(variableName, secondValue);
    Term outputOfSecond(substitution.performSubstitutionTo(term));
    if(outputOfFirst.isConstant() && outputOfSecond.isConstant())
    {
        AlbaNumber outputValueOfFirst(outputOfFirst.getConstantValueConstReference());
        AlbaNumber outputValueOfSecond(outputOfSecond.getConstantValueConstReference());
        SolutionSet continuityDomain(getContinuityDomain(term));
        AlbaNumberIntervals const& continuityDomainIntervals(continuityDomain.getAcceptedIntervals());
        AlbaNumberInterval firstAndSecondInterval(createCloseEndpoint(firstValue), createCloseEndpoint(secondValue));
        bool areOutputValuesNotEqual = outputValueOfFirst != outputValueOfSecond;
        bool areFirstAndSecondIntervalInContinuousDomain = isIntervalInsideTheIntervals(firstAndSecondInterval, continuityDomainIntervals);
        bool isValueToTestBetweenFirstAndSecond = firstAndSecondInterval.isValueInsideTheInterval(valueToTest);
        result = areFirstAndSecondIntervalInContinuousDomain && areOutputValuesNotEqual && isValueToTestBetweenFirstAndSecond;
    }
    return result;
}

ContinuityType getContinuityTypeAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    ContinuityType result(ContinuityType::Unknown);
    SubstitutionOfVariablesToValues substitution{{variableName, value}};
    Term subtitutedResult(substitution.performSubstitutionTo(term));
    if(subtitutedResult.isConstant())
    {
        AlbaNumber limitAtValueInPositiveSide(getLimitAtAValueInThePositiveSide(term, variableName, value));
        AlbaNumber limitAtValueInNegativeSide(getLimitAtAValueInTheNegativeSide(term, variableName, value));
        if(isAlmostEqualForLimitChecking(limitAtValueInPositiveSide, limitAtValueInNegativeSide))
        {
            AlbaNumber const& subtitutedResultValue(subtitutedResult.getConstantValueConstReference());
            if(isAlmostEqualForLimitChecking(limitAtValueInPositiveSide, subtitutedResultValue))
            {
                result = ContinuityType::ContinuousAtBothSides;
            }
            else
            {
                result = ContinuityType::DiscontinuousWithRemovableDiscontinuity;
            }
        }
        else
        {
            result = ContinuityType::DiscontinuousWithEssentialDiscontinuity;
        }
    }
    return result;
}

SolutionSet getContinuityDomain(
        Term const& term)
{
    // Calculus Theorem:  A polynomial function is continuous at every number.
    // Calculus Theorem:  A rational function (polynomial over polynomial) is continuous at every number in its domain.
    // Calculus Observation:  A radical function is continuous at every number in its domain.
    // Calculus Theorem:  A sine function is continuous at every number.
    // Calculus Theorem:  A cosine function is continuous at every number.

    // This code is not accurate. How about piecewise function?
    return calculateDomainForTermWithOneVariable(term);
}

}

}
