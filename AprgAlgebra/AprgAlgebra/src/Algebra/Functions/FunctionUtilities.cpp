#include "FunctionUtilities.hpp"

#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba{

namespace algebra
{
namespace Functions
{

bool isFunctionContinuous(Function const& functionObject)
{
    strings continuousFunctionNames{"abs", "sin", "cos"};

    return any_of(continuousFunctionNames.cbegin(), continuousFunctionNames.cend(),
                  [&](string const& continuousFunctionName)
    {
        return continuousFunctionName == functionObject.getFunctionName();
    });
}

AlbaNumberPairs evaluateAndGetInputOutputPair(
        AlbaNumbers const& numbers,
        string const& variableName,        Function const& functionObject)
{
    AlbaNumberPairs result;
    SubstitutionOfVariablesToValues substitution;    for(AlbaNumber const& number : numbers)
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
