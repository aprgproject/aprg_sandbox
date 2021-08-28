#include "Continuity.hpp"

#include <Algebra/Constructs/ConstructUtilities.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Retrieval/FunctionsRetriever.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Solution/DomainAndRange/DomainAndRange.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace alba::algebra::DomainAndRange;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba{

namespace algebra
{
bool isContinuousAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value,
        LimitAtAValueApproachType const limitApproachType)
{
    bool result(false);
    SubstitutionOfVariablesToValues substitution{{variableName, value}};    Term subtitutedResult(substitution.performSubstitutionTo(term));
    if(subtitutedResult.isConstant())
    {
        AlbaNumber limitAtValue(getLimitAtAValueByApproachType(term, variableName, value, limitApproachType));
        AlbaNumber const& subtitutedResultValue(subtitutedResult.getConstantConstReference().getNumberConstReference());
        result = isAlmostEqualForLimitChecking(subtitutedResultValue, limitAtValue);
    }
    return result;
}
ContinuityType getContinuityTypeAt(
        Term const& term,
        string const& variableName,        AlbaNumber const& value)
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
            AlbaNumber const& subtitutedResultValue(subtitutedResult.getConstantConstReference().getNumberConstReference());
            if(isAlmostEqualForLimitChecking(limitAtValueInPositiveSide, subtitutedResultValue))
            {
                result = ContinuityType::ContinuousAtBothSides;
            }
            else
            {                result = ContinuityType::DiscontinuousWithRemovableDiscontinuity;
            }
        }
        else        {
            result = ContinuityType::DiscontinuousWithEssentialDiscontinuity;
        }
    }
    return result;
}

SolutionSet getContinuityDomain(
        Term const& term)
{
    SolutionSet continuityDomain;
    FunctionsRetriever functionsRetriever([](Function const& functionObject)
    {
        return isFunctionContinuous(functionObject);
    });
    if(functionsRetriever.getSavedData().empty())
    {
        continuityDomain = calculateDomainForTermWithOneVariable(term);
    }
    return continuityDomain;
}

}

}