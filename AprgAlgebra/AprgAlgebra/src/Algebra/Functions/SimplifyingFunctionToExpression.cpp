#include "SimplifyingFunctionToExpression.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

Expression simplifyTrigometricFunctionToExpressionIfPossible(Function const& functionAsParameter)
{
    Expression expression;
    Term const& inputTerm(getTermConstReferenceFromBaseTerm(functionAsParameter.getInputTermConstReference()));
    if("tan" == functionAsParameter.getFunctionName())
    {
        expression = createExpressionIfPossible({Term(sin(inputTerm)), Term("/"), Term(cos(inputTerm))});
    }
    else if("csc" == functionAsParameter.getFunctionName())
    {
        expression = createExpressionIfPossible({Term(1), Term("/"), Term(sin(inputTerm))});
    }
    else if("sec" == functionAsParameter.getFunctionName())
    {
        expression = createExpressionIfPossible({Term(1), Term("/"), Term(cos(inputTerm))});
    }
    else if("cot" == functionAsParameter.getFunctionName())
    {
        expression = createExpressionIfPossible({Term(cos(inputTerm)), Term("/"), Term(sin(inputTerm))});
    }
    return expression;
}

}

}
