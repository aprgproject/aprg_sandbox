#include "FunctionUtilities.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Functions
{

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        string const& variableName,
        Function const& functionObject)
{
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;
    for(AlbaNumber const& number : numbers)
    {
        substitution.putVariableWithValue(variableName, number);
        Term substituteTerm(substitution.performSubstitutionTo(functionObject));
        if(substituteTerm.isConstant())
        {
            result.emplace_back(
                        number,
                        substituteTerm.getConstantConstReference().getNumberConstReference());
        }
    }
    return result;
}

}

}

}
