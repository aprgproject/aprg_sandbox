#include "TermUtilities.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;

namespace alba{

namespace algebra
{

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        string const& variableName,        Term const& term)
{
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;    for(AlbaNumber const& number : numbers)
    {
        substitution.putVariableWithValue(variableName, number);
        Term substituteTerm(substitution.performSubstitutionTo(term));
        if(substituteTerm.isConstant())
        {
            result.emplace_back(number, substituteTerm.getConstantConstReference().getNumberConstReference());
        }
    }
    return result;
}

}

}
