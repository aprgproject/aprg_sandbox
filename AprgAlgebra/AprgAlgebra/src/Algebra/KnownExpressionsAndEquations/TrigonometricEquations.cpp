#include "TrigonometricEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Equation getTrigonometricPythagoreanIdentity(Term const& term)
{
    // sin(x)^2 + cos(x)^2 = 1

    Term leftSideTerm(createExpressionIfPossible({getSineSquared(term), Term("+"), getCosineSquared(term)}));
    return Equation(leftSideTerm, "=", Term(1));
}

Equation getSineEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& hypotenuse)
{
    // sin(x) = o/h

    Term leftSideTerm(sin(angle));
    Term rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, Term("/"), hypotenuse}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getCosineEquationOfRightTriangle(
        Term const& angle,
        Term const& adjacentSideOfAngle,
        Term const& hypotenuse)
{
    // cos(x) = a/h

    Term leftSideTerm(cos(angle));
    Term rightSideTerm(createExpressionIfPossible({adjacentSideOfAngle, Term("/"), hypotenuse}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getTangentEquationOfRightTriangle(
        Term const& angle,
        Term const& oppositeSideOfAngle,
        Term const& adjacentSideOfAngle)
{
    // (x) = o/a

    Term leftSideTerm(tan(angle));
    Term rightSideTerm(createExpressionIfPossible({oppositeSideOfAngle, Term("/"), adjacentSideOfAngle}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getLawOfSineEquation(
        Term const& side1,
        Term const& oppositeAngleOfSide1,
        Term const& side2,
        Term const& oppositeAngleOfSide2)
{
    // x/sin(angleOppositeOfX) = y/sin(angleOppositeOfY) = z/sin(angleOppositeOfZ)

    Term leftSideTerm(createExpressionIfPossible({side1, Term("/"), sin(oppositeAngleOfSide1)}));
    Term rightSideTerm(createExpressionIfPossible({side2, Term("/"), sin(oppositeAngleOfSide2)}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Equation getLawOfCosineEquation(
        Term const& side1,
        Term const& side2,
        Term const& side3,
        Term const& oppositeAngleOfSide1)
{
    // x^2 = y^2 + z^2 - 2*y*z*cos(angleOppositeOfX)

    Term side1Squared(createExpressionIfPossible({side1, Term("^"), Term(2)}));
    Term side2Squared(createExpressionIfPossible({side2, Term("^"), Term(2)}));
    Term side3Squared(createExpressionIfPossible({side3, Term("^"), Term(2)}));
    Term cosinePart(createExpressionIfPossible({Term(2), Term("*"), side2, Term("*"), side3, Term("*"), Term(cos(oppositeAngleOfSide1))}));
    Term const& leftSideTerm(side1Squared);
    Term rightSideTerm(createExpressionIfPossible({side2Squared, Term("+"), side3Squared, Term("-"), cosinePart}));
    return Equation(leftSideTerm, "=", Term(rightSideTerm));
}

Term getSineSquared(Term const& term)
{
    // sin(x)^2

    return Term(createExpressionIfPossible({Term(sin(term)), Term("^"), Term(2)}));
}

Term getCosineSquared(Term const& term)
{
    // cos(x)^2

    return Term(createExpressionIfPossible({Term(cos(term)), Term("^"), Term(2)}));
}

Term getTangentSquared(Term const& term)
{
    // tan(x)^2

    return Term(createExpressionIfPossible({Term(tan(term)), Term("^"), Term(2)}));
}

Term getSineOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // sin(x +- y) =  sin(x)*cos(y) +- cos(x)*sin(y)

    Term result;
    if(operatorObject.isAddition() || operatorObject.isSubtraction())
    {
        Term firstPart(createExpressionIfPossible({Term(sin(term1)), Term("*"), Term(cos(term2))}));
        Term secondPart(createExpressionIfPossible({Term(cos(term1)), Term("*"), Term(sin(term2))}));
        result = Term(createExpressionIfPossible({firstPart, Term(operatorObject), secondPart}));
    }
    return result;
}

Term getCosineOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // cos(x +- y) =  cos(x)*cos(y) -+ sin(x)*sin(y)

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

Term getTangentOfSumOrDifferenceOfTwoTerms(
        Term const& term1,
        Operator const& operatorObject,
        Term const& term2)
{
    // tan(x +- y) =  (tan(x) +- tan(y)) / (1 -+ tan(x)*tan(y))

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
    // sin(2*x) =  2*sin(x)*cos(x)

    return Term(createExpressionIfPossible({Term(2), Term("*"), Term(sin(term)), Term("*"), Term(cos(term))}));
}

Term getCosineOfDoubledValue(Term const& term)
{
    // cos(2*x) =  cos(x)^2 - sin(x)^2

    return Term(createExpressionIfPossible({getCosineSquared(term), Term("-"), getSineSquared(term)}));
}

Term getTangentOfDoubledValue(Term const& term)
{
    // tan(2*x) =  (2*tan(x)) / (1-tan(x)^2)

    Term numerator(createExpressionIfPossible({Term(2), Term("*"), Term(tan(term))}));
    Term denominator(createExpressionIfPossible({Term(1), Term("-"), getTangentSquared(term)}));
    return Term(createExpressionIfPossible({numerator, Term("/"), denominator}));
}

Term getSineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // sin(x/2) =  +- ((1-cos(x))/2)^(1/2)

    Term numerator(createExpressionIfPossible({Term(1), Term("-"), Term(cos(term))}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({Term(-1), Term("*"), Term(result)}));
    }
    return result;
}

Term getCosineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // sin(x/2) =  +- ((1+cos(x))/2)^(1/2)

    Term numerator(createExpressionIfPossible({Term(1), Term("+"), Term(cos(term))}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, Term("/"), Term(2)}));
    Term result(createExpressionIfPossible({insideSquareRoot, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({Term(-1), Term("*"), Term(result)}));
    }
    return result;
}

}

}
