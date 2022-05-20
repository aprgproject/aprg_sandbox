#include "HyperbolicEquations.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

Term getEToTheX(
        Term const& term)
{
    // e^x

    return Term(createExpressionIfPossible({getEAsATerm(), "^", term}));
}

Term getEToTheNegativeX(
        Term const& term)
{
    // e^(-x)

    return Term(createExpressionIfPossible({getEAsATerm(), "^", negateTerm(term)}));
}

Term getEToTheXPlusEToTheNegativeX(
        Term const& term)
{
    // e^x + e^(-x)

    return Term(createExpressionIfPossible({getEToTheX(term), "+", getEToTheNegativeX(term)}));
}

Term getEToTheXMinusEToTheNegativeX(
        Term const& term)
{
    // e^x - e^(-x)

    return Term(createExpressionIfPossible({getEToTheX(term), "-", getEToTheNegativeX(term)}));
}

Equation getHyperbolicSineDefinition(
        Term const& term)
{
    // sinh(x) = (e^x - e^(-x)) / 2

    Term leftSideTerm(sinh(term));
    Term rightSideTerm(createExpressionIfPossible({getEToTheXMinusEToTheNegativeX(term), "/", 2}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicCosineDefinition(
        Term const& term)
{
    // cosh(x) = (e^x + e^(-x)) / 2

    Term leftSideTerm(cosh(term));
    Term rightSideTerm(createExpressionIfPossible({getEToTheXPlusEToTheNegativeX(term), "/", 2}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicTangentDefinition(
        Term const& term)
{
    // tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))

    Term leftSideTerm(tanh(term));
    Term rightSideTerm(createExpressionIfPossible(
    {getEToTheXMinusEToTheNegativeX(term), "/", getEToTheXPlusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicCosecantDefinition(
        Term const& term)
{
    // csch(x) = 2 / (e^x - e^(-x))

    Term leftSideTerm(csch(term));
    Term rightSideTerm(createExpressionIfPossible({2, "/", getEToTheXMinusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicSecantDefinition(
        Term const& term)
{
    // sech(x) = 2 / (e^x + e^(-x))

    Term leftSideTerm(sech(term));
    Term rightSideTerm(createExpressionIfPossible({2, "/", getEToTheXPlusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicCotangentDefinition(
        Term const& term)
{
    // coth(x) = (e^x + e^(-x)) / (e^x - e^(-x))

    Term leftSideTerm(coth(term));
    Term rightSideTerm(createExpressionIfPossible(
    {getEToTheXPlusEToTheNegativeX(term), "/", getEToTheXMinusEToTheNegativeX(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicFunctionIdentityEquation(
        Term const& term)
{
    // cosh(x)^2 - sinh(x)^2 = 1

    Term leftSideTerm(createExpressionIfPossible(
    {cosh(term), "^", 2, "-", sinh(term), "^", 2}));
    return Equation(leftSideTerm, "=", 1);
}

Equation getEToTheXFromHyperbolicFunctionsEquation(
        Term const& term)
{
    // e^x = cosh(x) + sinh(x)

    Term leftSideTerm(getEToTheX(term));
    Term rightSideTerm(createExpressionIfPossible({cosh(term), "+", sinh(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getEToTheNegativeXFromHyperbolicFunctionsEquation(
        Term const& term)
{
    // e^(-x) = cosh(x) - sinh(x)

    Term leftSideTerm(getEToTheNegativeX(term));
    Term rightSideTerm(createExpressionIfPossible({cosh(term), "-", sinh(term)}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Term getHyperbolicSineOfSumOfTwoTerms(
        Term const& term1,
        Term const& term2)
{
    // sinh(x + y) =  sinh(x)*cosh(y) + cosh(x)*sinh(y)

    Term firstPart(createExpressionIfPossible({sinh(term1), "*", cosh(term2)}));
    Term secondPart(createExpressionIfPossible({cosh(term1), "*", sinh(term2)}));
    return Term(createExpressionIfPossible({firstPart, "+", secondPart}));
}

Term getHyperbolicCosineOfSumOfTwoTerms(
        Term const& term1,
        Term const& term2)
{
    // cosh(x + y) =  cosh(x)*cosh(y) + sinh(x)*sinh(y)

    Term firstPart(createExpressionIfPossible({cosh(term1), "*", cosh(term2)}));
    Term secondPart(createExpressionIfPossible({sinh(term1), "*", sinh(term2)}));
    return Term(createExpressionIfPossible({firstPart, "+", secondPart}));
}

Term getHyperbolicSineOfDoubledValue(Term const& term)
{
    // sinh(2*x) =  2*sinh(x)*cosh(x)

    return Term(createExpressionIfPossible({2, "*", sinh(term), "*", cosh(term)}));
}

Term getHyperbolicCosineOfDoubledValue(Term const& term)
{
    // cosh(2*x) =  cosh(x)^2 + sinh(x)^2

    return Term(createExpressionIfPossible(
    {cosh(term), "^", 2, "+", sinh(term), "^", 2}));
}

Term getHyperbolicSineOfHalvedValue(Term const& term, bool const isPositiveRoot)
{
    // sinh(x/2) =  +- ((cosh(x)-1)/2)^(1/2)

    Term numerator(createExpressionIfPossible({cosh(term), "-", 1}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, "/", 2}));
    Term result(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    if(!isPositiveRoot)
    {
        result = Term(createExpressionIfPossible({-1, "*", result}));
    }
    return result;
}

Term getHyperbolicCosineOfHalvedValue(Term const& term)
{
    // sinh(x/2) = ((cosh(x)+1)/2)^(1/2)

    Term numerator(createExpressionIfPossible({cosh(term), "+", 1}));
    Term insideSquareRoot(createExpressionIfPossible({numerator, "/", 2}));
    Term result(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    return result;
}

Equation getHyperbolicArcSineDefinition(
        Term const& term)
{
    Term leftSideTerm(arcsinh(term));
    Term insideSquareRoot(createExpressionIfPossible({term, "^", 2, "+", 1}));
    Term squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    Term rightSideTerm(ln(insideLogarithm));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicArcCosineDefinition(
        Term const& term)
{
    Term leftSideTerm(arccosh(term));
    Term insideSquareRoot(createExpressionIfPossible({term, "^", 2, "-", 1}));
    Term squareRootTerm(createExpressionIfPossible({insideSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term insideLogarithm(createExpressionIfPossible({term, "+", squareRootTerm}));
    Term rightSideTerm(ln(insideLogarithm));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicArcTangentDefinition(
        Term const& term)
{
    Term leftSideTerm(arctanh(term));
    Term oneMinusTerm(createExpressionIfPossible({1, "-", term}));
    Term onePlusTerm(createExpressionIfPossible({1, "+", term}));
    Term insideLogarithm(createExpressionIfPossible({oneMinusTerm, "/", onePlusTerm}));
    Term logarithmTerm(ln(insideLogarithm));
    Term rightSideTerm(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

Equation getHyperbolicArcCotangentDefinition(
        Term const& term)
{
    Term leftSideTerm(arccoth(term));
    Term termPlusOne(createExpressionIfPossible({term, "+", 1}));
    Term termMinusOne(createExpressionIfPossible({term, "-", 1}));
    Term insideLogarithm(createExpressionIfPossible({termPlusOne, "/", termMinusOne}));
    Term logarithmTerm(ln(insideLogarithm));
    Term rightSideTerm(createExpressionIfPossible({AlbaNumber::createFraction(1, 2), "*", logarithmTerm}));
    return Equation(leftSideTerm, "=", rightSideTerm);
}

}

}
