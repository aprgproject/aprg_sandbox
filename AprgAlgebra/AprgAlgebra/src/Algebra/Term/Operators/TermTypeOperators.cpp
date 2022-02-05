#include "TermTypeOperators.hpp"

#include <Algebra/Operations/PerformOperations.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

Term createTermWithAnExpressionAdding2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithAdditionIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermAddingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionSubtracting2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithSubtractionIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermSubtractingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionMultiplying2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithMultiplicationIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermMultiplyingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionDividing2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithDivisionIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermDividingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionRaisingToPower2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(term1);
    newExpression.putTermWithRaiseToPowerIfNeeded(term2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermRaisingToPowerAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(term);
    return convertExpressionToSimplestTerm(newExpression);
}

}


//Unary plus: +a

Term operator+(Constant const& constant)
{
    return constant;
}

Term operator+(Variable const& variable)
{
    return variable;
}

Term operator+(Monomial const& monomial)
{
    return monomial;
}

Term operator+(Polynomial const& polynomial)
{
    return polynomial;
}

Term operator+(Expression const& expression)
{
    return expression;
}

Term operator+(Function const& functionObject)
{
    return functionObject;
}


//Unary minus: -a

Term operator-(Constant const& constant)
{
    return constant.getNumberConstReference()*-1;
}

Term operator-(Variable const& variable)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(-1, {{variable.getVariableName(), 1}}));
}

Term operator-(Monomial const& monomial)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference()));
}

Term operator-(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyNumber(-1);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(-1, expression);
}

Term operator-(Function const& functionObject)
{
    return createTermWithAnExpressionMultiplying2Terms(-1, functionObject);
}


//Addition: a + b

Term operator+(Constant const& constant1, Constant const& constant2)
{
    return constant1.getNumberConstReference() + constant2.getNumberConstReference();
}

Term operator+(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromNumber(constant.getNumberConstReference()),
                    createMonomialFromVariable(variable)
                });
}

Term operator+(Constant const& constant, Monomial const& monomial)
{
    if(isConstantOnly(monomial))
    {
        return constant.getNumberConstReference() + monomial.getConstantConstReference();
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromNumber(constant.getNumberConstReference()),
                        monomial
                    });
    }
}

Term operator+(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial;
    newPolynomial.addMonomial(createMonomialFromNumber(constant.getNumberConstReference()));
    newPolynomial.addPolynomial(polynomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(constant, expression);
}

Term operator+(Constant const& constant, Function const& functionObject)
{
    return createTermWithAnExpressionAdding2Terms(constant, functionObject);
}

Term operator+(Constant const& constant, Term const& term)
{
    return performAddition(constant, term);
}

Term operator+(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromVariable(variable),
                    createMonomialFromNumber(constant.getNumberConstReference())
                });
}

Term operator+(Variable const& variable1, Variable const& variable2)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(variable1, variable2))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(2, {{variable1.getVariableName(), 1}}));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromVariable(variable1),
                        createMonomialFromVariable(variable2)
                    });
    }
}

Term operator+(Variable const& variable, Monomial const& monomial)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromVariable(variable),
                        monomial
                    });
    }
}

Term operator+(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial;
    newPolynomial.addMonomial(createMonomialFromVariable(variable));
    newPolynomial.addPolynomial(polynomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(variable, expression);
}

Term operator+(Variable const& variable, Function const& functionObject)
{
    return createTermWithAnExpressionAdding2Terms(variable, functionObject);
}

Term operator+(Variable const& variable, Term const& term)
{
    return performAddition(variable, term);
}

Term operator+(Monomial const& monomial, Constant const& constant)
{
    if(isConstantOnly(monomial))
    {
        return monomial.getConstantConstReference() + constant.getNumberConstReference();
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial,
                        createMonomialFromNumber(constant.getNumberConstReference())
                    });
    }
}

Term operator+(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial,
                        createMonomialFromVariable(variable)
                    });
    }
}

Term operator+(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial2))
    {
        return simplifyAndConvertMonomialToSimplestTerm(
                    Monomial(
                        monomial1.getConstantConstReference()+monomial2.getConstantConstReference(),
                        monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(Polynomial{monomial1, monomial2});
    }
}

Term operator+(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(createPolynomialFromMonomial(monomial));
    newPolynomial.addPolynomial(polynomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(monomial, expression);
}

Term operator+(Monomial const& monomial, Function const& functionObject)
{
    return createTermWithAnExpressionAdding2Terms(monomial, functionObject);
}

Term operator+(Monomial const& monomial, Term const& term)
{
    return performAddition(monomial, term);
}

Term operator+(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(createMonomialFromNumber(constant.getNumberConstReference()));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(createMonomialFromVariable(variable));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(monomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    newPolynomial.addPolynomial(polynomial2);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(polynomial, expression);
}

Term operator+(Polynomial const& polynomial, Function const& functionObject)
{
    return createTermWithAnExpressionAdding2Terms(polynomial, functionObject);
}

Term operator+(Polynomial const& polynomial, Term const& term)
{
    return performAddition(polynomial, term);
}

Term operator+(Expression const& expression, Constant const& constant)
{
    return createTermAddingAnExpressionAndATerm(expression, constant);
}

Term operator+(Expression const& expression, Variable const& variable)
{
    return createTermAddingAnExpressionAndATerm(expression, variable);
}

Term operator+(Expression const& expression, Monomial const& monomial)
{
    return createTermAddingAnExpressionAndATerm(expression, monomial);
}

Term operator+(Expression const& expression, Polynomial const& polynomial)
{
    return createTermAddingAnExpressionAndATerm(expression, polynomial);
}

Term operator+(Expression const& expression1, Expression const& expression2)
{
    return createTermAddingAnExpressionAndATerm(expression1, expression2);
}

Term operator+(Expression const& expression, Function const& functionObject)
{
    return createTermAddingAnExpressionAndATerm(expression, functionObject);
}

Term operator+(Expression const& expression, Term const& term)
{
    return performAddition(expression, term);
}

Term operator+(Function const& functionObject, Constant const& constant)
{
    return createTermWithAnExpressionAdding2Terms(functionObject, constant);
}

Term operator+(Function const& functionObject, Variable const& variable)
{
    return createTermWithAnExpressionAdding2Terms(functionObject, variable);
}

Term operator+(Function const& functionObject, Monomial const& monomial)
{
    return createTermWithAnExpressionAdding2Terms(functionObject, monomial);
}

Term operator+(Function const& functionObject, Polynomial const& polynomial)
{
    return createTermWithAnExpressionAdding2Terms(functionObject, polynomial);
}

Term operator+(Function const& functionObject, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(functionObject, expression);
}

Term operator+(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionAdding2Terms(function1, function2);
}

Term operator+(Function const& functionObject, Term const& term)
{
    return performAddition(functionObject, term);
}

Term operator+(Term const& term, Constant const& constant)
{
    return performAddition(term, constant);
}

Term operator+(Term const& term, Variable const& variable)
{
    return performAddition(term, variable);
}

Term operator+(Term const& term, Monomial const& monomial)
{
    return performAddition(term, monomial);
}

Term operator+(Term const& term, Polynomial const& polynomial)
{
    return performAddition(term, polynomial);
}

Term operator+(Term const& term, Expression const& expression)
{
    return performAddition(term, expression);
}

Term operator+(Term const& term, Function const& functionObject)
{
    return performAddition(term, functionObject);
}


//Subtraction: a - b

Term operator-(Constant const& constant1, Constant const& constant2)
{
    return constant1.getNumberConstReference() - constant2.getNumberConstReference();
}

Term operator-(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromNumber(constant.getNumberConstReference()),
                    Monomial(-1, {{variable.getVariableName(), 1}})
                });
}

Term operator-(Constant const& constant, Monomial const& monomial)
{
    if(isConstantOnly(monomial))
    {
        return constant.getNumberConstReference() - monomial.getConstantConstReference();
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromNumber(constant.getNumberConstReference()),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial{createMonomialFromNumber(constant.getNumberConstReference())};
    Polynomial subtrahend(polynomial);
    subtrahend.multiplyNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(constant, expression);
}

Term operator-(Constant const& constant, Function const& functionObject)
{
    return createTermWithAnExpressionSubtracting2Terms(constant, functionObject);
}

Term operator-(Constant const& constant, Term const& term)
{
    return performSubtraction(constant, term);
}

Term operator-(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromVariable(variable),
                    Monomial(constant.getNumberConstReference()*-1, {})
                });
}

Term operator-(Variable const& variable1, Variable const& variable2)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(variable1, variable2))
    {
        return AlbaNumber(0);
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromVariable(variable1),
                        Monomial(-1, {{variable2.getVariableName(), 1}})
                    });
    }
}

Term operator-(Variable const& variable, Monomial const& monomial)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(AlbaNumber(1)-monomial.getConstantConstReference(), {{variable.getVariableName(), 1}}));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromVariable(variable),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial{createMonomialFromVariable(variable)};
    Polynomial subtrahend(polynomial);
    subtrahend.multiplyNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(variable, expression);
}

Term operator-(Variable const& variable, Function const& functionObject)
{
    return createTermWithAnExpressionSubtracting2Terms(variable, functionObject);
}

Term operator-(Variable const& variable, Term const& term)
{
    return performSubtraction(variable, term);
}

Term operator-(Monomial const& monomial, Constant const& constant)
{
    if(isConstantOnly(monomial))
    {
        return monomial.getConstantConstReference() - constant.getNumberConstReference();
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial,
                        Monomial(constant.getNumberConstReference()*-1, {})
                    });
    }
}

Term operator-(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()-1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial,
                        Monomial(-1, {{variable.getVariableName(), 1}})
                    });
    }
}

Term operator-(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial1, monomial2))
    {
        return simplifyAndConvertMonomialToSimplestTerm(
                    Monomial(
                        monomial1.getConstantConstReference()-monomial2.getConstantConstReference(),
                        monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial1,
                        Monomial(monomial2.getConstantConstReference()*-1, monomial2.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(createPolynomialFromMonomial(monomial));
    Polynomial subtrahend(polynomial);
    subtrahend.multiplyNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(monomial, expression);
}

Term operator-(Monomial const& monomial, Function const& functionObject)
{
    return createTermWithAnExpressionSubtracting2Terms(monomial, functionObject);
}

Term operator-(Monomial const& monomial, Term const& term)
{
    return performSubtraction(monomial, term);
}

Term operator-(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference()*-1, {}));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(-1, {{variable.getVariableName(), 1}}));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference()));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    Polynomial subtrahend(polynomial2);
    subtrahend.multiplyNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(polynomial, expression);
}

Term operator-(Polynomial const& polynomial, Function const& functionObject)
{
    return createTermWithAnExpressionSubtracting2Terms(polynomial, functionObject);
}

Term operator-(Polynomial const& polynomial, Term const& term)
{
    return performSubtraction(polynomial, term);
}

Term operator-(Expression const& expression, Constant const& constant)
{
    return createTermSubtractingAnExpressionAndATerm(expression, constant);
}

Term operator-(Expression const& expression, Variable const& variable)
{
    return createTermSubtractingAnExpressionAndATerm(expression, variable);
}

Term operator-(Expression const& expression, Monomial const& monomial)
{
    return createTermSubtractingAnExpressionAndATerm(expression, monomial);
}

Term operator-(Expression const& expression, Polynomial const& polynomial)
{
    return createTermSubtractingAnExpressionAndATerm(expression, polynomial);
}

Term operator-(Expression const& expression1, Expression const& expression2)
{
    return createTermSubtractingAnExpressionAndATerm(expression1, expression2);
}

Term operator-(Expression const& expression, Function const& functionObject)
{
    return createTermSubtractingAnExpressionAndATerm(expression, functionObject);
}

Term operator-(Expression const& expression, Term const& term)
{
    return performSubtraction(expression, term);
}

Term operator-(Function const& functionObject, Constant const& constant)
{
    return createTermWithAnExpressionSubtracting2Terms(functionObject, constant);
}

Term operator-(Function const& functionObject, Variable const& variable)
{
    return createTermWithAnExpressionSubtracting2Terms(functionObject, variable);
}

Term operator-(Function const& functionObject, Monomial const& monomial)
{
    return createTermWithAnExpressionSubtracting2Terms(functionObject, monomial);
}

Term operator-(Function const& functionObject, Polynomial const& polynomial)
{
    return createTermWithAnExpressionSubtracting2Terms(functionObject, polynomial);
}

Term operator-(Function const& functionObject, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(functionObject, expression);
}

Term operator-(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionSubtracting2Terms(function1, function2);
}

Term operator-(Function const& functionObject, Term const& term)
{
    return performSubtraction(functionObject, term);
}

Term operator-(Term const& term, Constant const& constant)
{
    return performSubtraction(term, constant);
}

Term operator-(Term const& term, Variable const& variable)
{
    return performSubtraction(term, variable);
}

Term operator-(Term const& term, Monomial const& monomial)
{
    return performSubtraction(term, monomial);
}

Term operator-(Term const& term, Polynomial const& polynomial)
{
    return performSubtraction(term, polynomial);
}

Term operator-(Term const& term, Expression const& expression)
{
    return performSubtraction(term, expression);
}

Term operator-(Term const& term, Function const& functionObject)
{
    return performSubtraction(term, functionObject);
}


//Multiplication: a * b

Term operator*(Constant const& constant1, Constant const& constant2)
{
    return constant1.getNumberConstReference() * constant2.getNumberConstReference();
}

Term operator*(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Constant const& constant, Monomial const& monomial)
{
    return simplifyAndConvertMonomialToSimplestTerm(
                Monomial(
                    constant.getNumberConstReference()*monomial.getConstantConstReference(),
                    monomial.getVariablesToExponentsMapConstReference()));
}

Term operator*(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyNumber(constant.getNumberConstReference());
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(constant, expression);
}

Term operator*(Constant const& constant, Function const& functionObject)
{
    return createTermWithAnExpressionMultiplying2Terms(constant, functionObject);
}

Term operator*(Constant const& constant, Term const& term)
{
    return performMultiplication(constant, term);
}

Term operator*(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 2}}));
    }
    else
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), 1}}));
    }
}

Term operator*(Variable const& variable, Monomial const& monomial)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        Monomial newMonomial(createMonomialFromVariable(variable));
        newMonomial.multiplyMonomial(monomial);
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator*(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyMonomial(createMonomialFromVariable(variable));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(variable, expression);
}

Term operator*(Variable const& variable, Function const& functionObject)
{
    return createTermWithAnExpressionMultiplying2Terms(variable, functionObject);
}

Term operator*(Variable const& variable, Term const& term)
{
    return performMultiplication(variable, term);
}

Term operator*(Monomial const& monomial, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(
                Monomial(
                    monomial.getConstantConstReference()*constant.getNumberConstReference(),
                    monomial.getVariablesToExponentsMapConstReference()));
}

Term operator*(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        Monomial newMonomial(monomial);
        newMonomial.multiplyMonomial(createMonomialFromVariable(variable));
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator*(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial newMonomial(monomial1);
    newMonomial.multiplyMonomial(monomial2);
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator*(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyMonomial(monomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(monomial, expression);
}

Term operator*(Monomial const& monomial, Function const& functionObject)
{
    return createTermWithAnExpressionMultiplying2Terms(monomial, functionObject);
}

Term operator*(Monomial const& monomial, Term const& term)
{
    return performMultiplication(monomial, term);
}

Term operator*(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyNumber(constant.getNumberConstReference());
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyMonomial(createMonomialFromVariable(variable));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyMonomial(monomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    newPolynomial.multiplyPolynomial(polynomial2);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Expression const& expression)
{
    Expression newExpression(expression);
    newExpression.putPolynomialFirstWithMultiplication(polynomial);
    return convertExpressionToSimplestTerm(newExpression);
}

Term operator*(Polynomial const& polynomial, Function const& functionObject)
{
    return createTermWithAnExpressionMultiplying2Terms(polynomial, functionObject);
}

Term operator*(Polynomial const& polynomial, Term const& term)
{
    return performMultiplication(polynomial, term);
}

Term operator*(Expression const& expression, Constant const& constant)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, constant);
}

Term operator*(Expression const& expression, Variable const& variable)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, variable);
}

Term operator*(Expression const& expression, Monomial const& monomial)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, monomial);
}

Term operator*(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);
    newExpression.putPolynomialSecondWithMultiplication(polynomial);
    return convertExpressionToSimplestTerm(newExpression);
}

Term operator*(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putExpressionWithMultiplication(expression2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term operator*(Expression const& expression, Function const& functionObject)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, functionObject);
}

Term operator*(Expression const& expression, Term const& term)
{
    return performMultiplication(expression, term);
}

Term operator*(Function const& functionObject, Constant const& constant)
{
    return createTermWithAnExpressionMultiplying2Terms(functionObject, constant);
}

Term operator*(Function const& functionObject, Variable const& variable)
{
    return createTermWithAnExpressionMultiplying2Terms(functionObject, variable);
}

Term operator*(Function const& functionObject, Monomial const& monomial)
{
    return createTermWithAnExpressionMultiplying2Terms(functionObject, monomial);
}

Term operator*(Function const& functionObject, Polynomial const& polynomial)
{
    return createTermWithAnExpressionMultiplying2Terms(functionObject, polynomial);
}

Term operator*(Function const& functionObject, Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(functionObject, expression);
}

Term operator*(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionMultiplying2Terms(function1, function2);
}

Term operator*(Function const& functionObject, Term const& term)
{
    return performMultiplication(functionObject, term);
}

Term operator*(Term const& term, Constant const& constant)
{
    return performMultiplication(term, constant);
}

Term operator*(Term const& term, Variable const& variable)
{
    return performMultiplication(term, variable);
}

Term operator*(Term const& term, Monomial const& monomial)
{
    return performMultiplication(term, monomial);
}

Term operator*(Term const& term, Polynomial const& polynomial)
{
    return performMultiplication(term, polynomial);
}

Term operator*(Term const& term, Expression const& expression)
{
    return performMultiplication(term, expression);
}

Term operator*(Term const& term, Function const& functionObject)
{
    return performMultiplication(term, functionObject);
}


//Divsion: a / b

Term operator/(Constant const& constant1, Constant const& constant2)
{
    return constant1.getNumberConstReference() / constant2.getNumberConstReference();
}

Term operator/(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), -1}}));
}

Term operator/(Constant const& constant, Monomial const& monomial)
{
    Monomial newMonomial(createMonomialFromNumber(constant.getNumberConstReference()));
    newMonomial.divideMonomial(monomial);
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator/(Constant const& constant, Polynomial const& polynomial)
{
    return createExpressionIfPossible({constant, "/", polynomial});
}

Term operator/(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(constant, expression);
}

Term operator/(Constant const& constant, Function const& functionObject)
{
    return createTermWithAnExpressionDividing2Terms(constant, functionObject);
}

Term operator/(Constant const& constant, Term const& term)
{
    return performDivision(constant, term);
}

Term operator/(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(AlbaNumber(1)/constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator/(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return 1;
    }
    else
    {
        return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), -1}}));
    }
}

Term operator/(Variable const& variable, Monomial const& monomial)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return AlbaNumber(1)/monomial.getConstantConstReference();
    }
    else
    {
        Monomial newMonomial(createMonomialFromVariable(variable));
        newMonomial.divideMonomial(monomial);
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator/(Variable const& variable, Polynomial const& polynomial)
{
    return createExpressionIfPossible({variable, "/", polynomial});
}

Term operator/(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(variable, expression);
}

Term operator/(Variable const& variable, Function const& functionObject)
{
    return createTermWithAnExpressionDividing2Terms(variable, functionObject);
}

Term operator/(Variable const& variable, Term const& term)
{
    return performDivision(variable, term);
}

Term operator/(Monomial const& monomial, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(
                Monomial(
                    monomial.getConstantConstReference()/constant.getNumberConstReference(),
                    monomial.getVariablesToExponentsMapConstReference()));
}

Term operator/(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return monomial.getConstantConstReference();
    }
    else
    {
        Monomial newMonomial(monomial);
        newMonomial.divideMonomial(createMonomialFromVariable(variable));
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator/(Monomial const& monomial1, Monomial const& monomial2)
{
    Monomial newMonomial(monomial1);
    newMonomial.divideMonomial(monomial2);
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator/(Monomial const& monomial, Polynomial const& polynomial)
{
    return createExpressionIfPossible({monomial, "/", polynomial});
}

Term operator/(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(monomial, expression);
}

Term operator/(Monomial const& monomial, Function const& functionObject)
{
    return createTermWithAnExpressionDividing2Terms(monomial, functionObject);
}

Term operator/(Monomial const& monomial, Term const& term)
{
    return performDivision(monomial, term);
}

Term operator/(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.divideNumber(constant.getNumberConstReference());
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator/(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.divideMonomial(createMonomialFromVariable(variable));
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator/(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.divideMonomial(monomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator/(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    return createExpressionIfPossible({polynomial1, "/", polynomial2});
}

Term operator/(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(polynomial, expression);
}

Term operator/(Polynomial const& polynomial, Function const& functionObject)
{
    return createTermWithAnExpressionDividing2Terms(polynomial, functionObject);
}

Term operator/(Polynomial const& polynomial, Term const& term)
{
    return performDivision(polynomial, term);
}

Term operator/(Expression const& expression, Constant const& constant)
{
    return createTermDividingAnExpressionAndATerm(expression, constant);
}

Term operator/(Expression const& expression, Variable const& variable)
{
    return createTermDividingAnExpressionAndATerm(expression, variable);
}

Term operator/(Expression const& expression, Monomial const& monomial)
{
    return createTermDividingAnExpressionAndATerm(expression, monomial);
}

Term operator/(Expression const& expression, Polynomial const& polynomial)
{
    return createTermDividingAnExpressionAndATerm(expression, polynomial);
}

Term operator/(Expression const& expression1, Expression const& expression2)
{
    return createTermDividingAnExpressionAndATerm(expression1, expression2);
}

Term operator/(Expression const& expression, Function const& functionObject)
{
    return createTermDividingAnExpressionAndATerm(expression, functionObject);
}

Term operator/(Expression const& expression, Term const& term)
{
    return performDivision(expression, term);
}

Term operator/(Function const& functionObject, Constant const& constant)
{
    return createTermWithAnExpressionDividing2Terms(functionObject, constant);
}

Term operator/(Function const& functionObject, Variable const& variable)
{
    return createTermWithAnExpressionDividing2Terms(functionObject, variable);
}

Term operator/(Function const& functionObject, Monomial const& monomial)
{
    return createTermWithAnExpressionDividing2Terms(functionObject, monomial);
}

Term operator/(Function const& functionObject, Polynomial const& polynomial)
{
    return createTermWithAnExpressionDividing2Terms(functionObject, polynomial);
}

Term operator/(Function const& functionObject, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(functionObject, expression);
}

Term operator/(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionDividing2Terms(function1, function2);
}

Term operator/(Function const& functionObject, Term const& term)
{
    return performDivision(functionObject, term);
}

Term operator/(Term const& term, Constant const& constant)
{
    return performDivision(term, constant);
}

Term operator/(Term const& term, Variable const& variable)
{
    return performDivision(term, variable);
}

Term operator/(Term const& term, Monomial const& monomial)
{
    return performDivision(term, monomial);
}

Term operator/(Term const& term, Polynomial const& polynomial)
{
    return performDivision(term, polynomial);
}

Term operator/(Term const& term, Expression const& expression)
{
    return performDivision(term, expression);
}

Term operator/(Term const& term, Function const& functionObject)
{
    return performDivision(term, functionObject);
}


//RaiseToThePower: a ^ b

Term operator^(Constant const& constant1, Constant const& constant2)
{
    return constant1.getNumberConstReference() ^ constant2.getNumberConstReference();
}

Term operator^(Constant const& constant, Variable const& variable)
{
    return createExpressionIfPossible({constant, "^", variable});
}

Term operator^(Constant const& constant, Monomial const& monomial)
{
    if(isConstantOnly(monomial))
    {
        return constant.getNumberConstReference() ^ monomial.getConstantConstReference();
    }
    else
    {
        return createExpressionIfPossible({constant, "^", monomial});
    }
}

Term operator^(Constant const& constant, Polynomial const& polynomial)
{
    return createExpressionIfPossible({constant, "^", polynomial});
}

Term operator^(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(constant, expression);
}

Term operator^(Constant const& constant, Function const& functionObject)
{
    return createTermWithAnExpressionRaisingToPower2Terms(constant, functionObject);
}

Term operator^(Constant const& constant, Term const& term)
{
    return performRaiseToPower(constant, term);
}

Term operator^(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}}));
}

Term operator^(Variable const& variable1, Variable const& variable2)
{
    return createExpressionIfPossible({variable1, "^", variable2});
}

Term operator^(Variable const& variable, Monomial const& monomial)
{
    return createExpressionIfPossible({variable, "^", monomial});
}

Term operator^(Variable const& variable, Polynomial const& polynomial)
{
    return createExpressionIfPossible({variable, "^", polynomial});
}

Term operator^(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(variable, expression);
}

Term operator^(Variable const& variable, Function const& functionObject)
{
    return createTermWithAnExpressionRaisingToPower2Terms(variable, functionObject);
}

Term operator^(Variable const& variable, Term const& term)
{
    return performRaiseToPower(variable, term);
}

Term operator^(Monomial const& monomial, Constant const& constant)
{
    Monomial newMonomial(monomial);
    newMonomial.raiseToPowerNumber(constant.getNumberConstReference());
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator^(Monomial const& monomial, Variable const& variable)
{
    return createExpressionIfPossible({monomial, "^", variable});
}

Term operator^(Monomial const& monomial1, Monomial const& monomial2)
{
    return createExpressionIfPossible({monomial1, "^", monomial2});
}

Term operator^(Monomial const& monomial, Polynomial const& polynomial)
{
    return createExpressionIfPossible({monomial, "^", polynomial});
}

Term operator^(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(monomial, expression);
}

Term operator^(Monomial const& monomial, Function const& functionObject)
{
    return createTermWithAnExpressionRaisingToPower2Terms(monomial, functionObject);
}

Term operator^(Monomial const& monomial, Term const& term)
{
    return performRaiseToPower(monomial, term);
}

Term operator^(Polynomial const& polynomial, Constant const& constant)
{
    Term newTerm;
    AlbaNumber exponentNumber(constant.getNumberConstReference());
    if(exponentNumber.isIntegerType())
    {
        int exponentInteger(static_cast<int>(exponentNumber.getInteger()));
        if(exponentInteger == 0)
        {
            newTerm = 1;
        }
        else
        {
            unsigned int exponentAbsoluteValue(static_cast<unsigned int>(getAbsoluteValue(exponentInteger)));
            Polynomial newPolynomial(polynomial);
            newPolynomial.raiseToUnsignedInteger(exponentAbsoluteValue);
            if(exponentInteger > 0)
            {
                newTerm = simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
            }
            else
            {
                newTerm = createExpressionIfPossible({1, "/", simplifyAndConvertPolynomialToSimplestTerm(newPolynomial)});
            }
        }
    }
    else
    {
        newTerm = createExpressionIfPossible({polynomial, "^", constant});
    }
    return newTerm;
}

Term operator^(Polynomial const& polynomial, Variable const& variable)
{
    return createExpressionIfPossible({polynomial, "^", variable});
}

Term operator^(Polynomial const& polynomial, Monomial const& monomial)
{
    return createExpressionIfPossible({polynomial, "^", monomial});
}

Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    return createExpressionIfPossible({polynomial1, "^", polynomial2});
}

Term operator^(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(polynomial, expression);
}

Term operator^(Polynomial const& polynomial, Function const& functionObject)
{
    return createTermWithAnExpressionRaisingToPower2Terms(polynomial, functionObject);
}

Term operator^(Polynomial const& polynomial, Term const& term)
{
    return performRaiseToPower(polynomial, term);
}

Term operator^(Expression const& expression, Constant const& constant)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, constant);
}

Term operator^(Expression const& expression, Variable const& variable)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, variable);
}

Term operator^(Expression const& expression, Monomial const& monomial)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, monomial);
}

Term operator^(Expression const& expression, Polynomial const& polynomial)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, polynomial);
}

Term operator^(Expression const& expression1, Expression const& expression2)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression1, expression2);
}

Term operator^(Expression const& expression, Function const& functionObject)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, functionObject);
}

Term operator^(Expression const& expression, Term const& term)
{
    return performRaiseToPower(expression, term);
}

Term operator^(Function const& functionObject, Constant const& constant)
{
    return createTermWithAnExpressionRaisingToPower2Terms(functionObject, constant);
}

Term operator^(Function const& functionObject, Variable const& variable)
{
    return createTermWithAnExpressionRaisingToPower2Terms(functionObject, variable);
}

Term operator^(Function const& functionObject, Monomial const& monomial)
{
    return createTermWithAnExpressionRaisingToPower2Terms(functionObject, monomial);
}

Term operator^(Function const& functionObject, Polynomial const& polynomial)
{
    return createTermWithAnExpressionRaisingToPower2Terms(functionObject, polynomial);
}

Term operator^(Function const& functionObject, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(functionObject, expression);
}

Term operator^(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionRaisingToPower2Terms(function1, function2);
}

Term operator^(Function const& functionObject, Term const& term)
{
    return performRaiseToPower(functionObject, term);
}

Term operator^(Term const& term, Constant const& constant)
{
    return performRaiseToPower(term, constant);
}

Term operator^(Term const& term, Variable const& variable)
{
    return performRaiseToPower(term, variable);
}

Term operator^(Term const& term, Monomial const& monomial)
{
    return performRaiseToPower(term, monomial);
}

Term operator^(Term const& term, Polynomial const& polynomial)
{
    return performRaiseToPower(term, polynomial);
}

Term operator^(Term const& term, Expression const& expression)
{
    return performRaiseToPower(term, expression);
}

Term operator^(Term const& term, Function const& functionObject)
{
    return performRaiseToPower(term, functionObject);
}

}

}
