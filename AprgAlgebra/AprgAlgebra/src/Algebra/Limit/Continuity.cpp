#include "Continuity.hpp"

#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

bool isContinuousAt(
        Term const& term,
        string const& variableName,
        AlbaNumber const& value)
{
    bool result(false);
    SubstitutionOfVariablesToValues substitution{{variableName, value}};
    Term subtitutedResult(substitution.performSubstitutionTo(term));
    if(subtitutedResult.isConstant())
    {
        AlbaNumber limitAtValue(getLimitAtAValueInBothSides(term, variableName, value));
        result = subtitutedResult.getConstantConstReference().getNumberConstReference() == limitAtValue;
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
        if(limitAtValueInPositiveSide == limitAtValueInNegativeSide)
        {
            if(limitAtValueInPositiveSide == subtitutedResult.getConstantConstReference().getNumberConstReference())
            {
                result = ContinuityType::Continuous;
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

}

}
