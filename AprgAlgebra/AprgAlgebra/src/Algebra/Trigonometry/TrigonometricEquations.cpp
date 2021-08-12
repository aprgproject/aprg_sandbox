#include "TrigonometricEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Equation getSineSquaredPlusCosineSquaredEqualsOne(Term const& term)
{
    Term leftSideTerm(createExpressionIfPossible({getSineSquared(term), Term("+"), getCosineSquared(term)}));
    return Equation(leftSideTerm, "=", Term(1));
}

Term getSineSquared(Term const& term)
{
    return Term(createExpressionIfPossible({Term(sin(term)), Term("^"), Term(2)}));
}

Term getCosineSquared(Term const& term)
{
    return Term(createExpressionIfPossible({Term(cos(term)), Term("^"), Term(2)}));
}

Term getTangentSquared(Term const& term)
{
    return Term(createExpressionIfPossible({Term(tan(term)), Term("^"), Term(2)}));
}

Term getSineOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Term firstPart(createExpressionIfPossible({Term(sin(term1)), Term("*"), Term(cos(term2))}));
        Term secondPart(createExpressionIfPossible({Term(cos(term1)), Term("*"), Term(sin(term2))}));
        result = Term(createExpressionIfPossible({firstPart, Term(operatorObject), secondPart}));
    }
    return result;
}

Term getCosineOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Term firstPart(createExpressionIfPossible({Term(cos(term1)), Term("*"), Term(cos(term2))}));
        Term secondPart(createExpressionIfPossible({Term(sin(term1)), Term("*"), Term(sin(term2))}));
        Operator reverseOperator(operatorObject);
        reverseOperator.reverseOperation();
        result = Term(createExpressionIfPossible({firstPart, Term(reverseOperator), secondPart}));
    }
    return result;
}

Term getTangentOfSumOrDifferenceOfTwoVariables(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Operator reverseOperator(operatorObject);
        reverseOperator.reverseOperation();
        Term numerator(createExpressionIfPossible({Term(tan(term1)), Term(operatorObject), Term(tan(term2))}));
        Term denominator(createExpressionIfPossible(
        {Term(1), Term(reverseOperator), Term(createExpressionIfPossible({Term(tan(term1)), Term("*"), Term(tan(term2))}))}));
        result = Term(createExpressionIfPossible({numerator, Term("/"), denominator}));
    }
    return result;
}

Term getSineOfDoubledValue(Term const& term)
{
    return Term(createExpressionIfPossible({Term(2), Term("*"), Term(sin(term)), Term("*"), Term(cos(term))}));
}

Term getCosineOfDoubledValue(Term const& term)
{
    return Term(createExpressionIfPossible({getCosineSquared(term), Term("-"), getSineSquared(term)}));
}

Term getTangentOfDoubledValue(Term const& term)
{
    Term numerator(createExpressionIfPossible({Term(2), Term("*"), Term(tan(term))}));
    Term denominator(createExpressionIfPossible({Term(1), Term("-"), getTangentSquared(term)}));
    return Term(createExpressionIfPossible({numerator, Term("/"), denominator}));
}

Term getSineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    Term numerator(createExpressionIfPossible({Term(1), Term("-"), Term(cos(term))}));
    Term squaredValue(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({squaredValue, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({Term(-1), Term("*"), Term(result)}));
    }
    return result;
}

Term getCosineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    Term numerator(createExpressionIfPossible({Term(1), Term("+"), Term(cos(term))}));
    Term squaredValue(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({squaredValue, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({Term(-1), Term("*"), Term(result)}));
    }
    return result;
}

}

}
