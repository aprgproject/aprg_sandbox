#include "TermOperators.hpp"

#include <Equation/Operations/PerformOperations.hpp>
#include <Equation/Utilities.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

Term createTermWithAnExpressionAdding2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(term1));
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(term2));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermAddingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(term));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionSubtracting2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(term1));
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(term2));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermSubtractingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(term));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionMultiplying2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(term1));
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(term2));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermMultiplyingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(term));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionDividing2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(term1));
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(term2));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermDividingAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(term));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermWithAnExpressionRaisingToPower2Terms(Term const& term1, Term const& term2)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(term1));
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(term2));
    return convertExpressionToSimplestTerm(newExpression);
}

Term createTermRaisingToPowerAnExpressionAndATerm(Expression const& expression, Term const& term)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(term));
    return convertExpressionToSimplestTerm(newExpression);
}



//Unary plus: +a

Term operator+(Constant const& constant)
{
    return Term(constant);
}

Term operator+(Variable const& variable)
{
    return Term(variable);
}

Term operator+(Monomial const& monomial)
{
    return Term(monomial);
}

Term operator+(Polynomial const& polynomial)
{
    return Term(polynomial);
}

Term operator+(Expression const& expression)
{
    return Term(expression);
}

Term operator+(Function const& functionAsParameter)
{
    return Term(functionAsParameter);
}

Term operator+(Term const& term)
{
    return performUnaryPlus(term);
}


//Unary minus: -a

Term operator-(Constant const& constant)
{
    return Term(constant.getNumberConstReference()*-1);
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
    return createTermWithAnExpressionMultiplying2Terms(Term(-1), Term(expression));
}

Term operator-(Function const& functionAsParameter)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(-1), Term(functionAsParameter));
}

Term operator-(Term const& term)
{
    return performUnaryMinus(term);
}


//Addition: a + b

Term operator+(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() + constant2.getNumberConstReference());
}

Term operator+(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromConstant(constant),
                    createMonomialFromVariable(variable)
                });
}

Term operator+(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() + monomial.getConstantConstReference());
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromConstant(constant),
                        monomial
                    });
    }
}

Term operator+(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial;
    newPolynomial.addMonomial(createMonomialFromConstant(constant));
    newPolynomial.addPolynomial(polynomial);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator+(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(Term(constant), Term(expression));
}

Term operator+(Constant const& constant, Function const& functionAsParameter)
{
    return createTermWithAnExpressionAdding2Terms(Term(constant), Term(functionAsParameter));
}

Term operator+(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromVariable(variable),
                    createMonomialFromConstant(constant)
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
    return createTermWithAnExpressionAdding2Terms(Term(variable), Term(expression));
}

Term operator+(Variable const& variable, Function const& functionAsParameter)
{
    return createTermWithAnExpressionAdding2Terms(Term(variable), Term(functionAsParameter));
}

Term operator+(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() + constant.getNumberConstReference());
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        monomial,
                        createMonomialFromConstant(constant)
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
    return createTermWithAnExpressionAdding2Terms(Term(monomial), Term(expression));
}

Term operator+(Monomial const& monomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionAdding2Terms(Term(monomial), Term(functionAsParameter));
}

Term operator+(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(createMonomialFromConstant(constant));
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
    return createTermWithAnExpressionAdding2Terms(Term(polynomial), Term(expression));
}

Term operator+(Polynomial const& polynomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionAdding2Terms(Term(polynomial), Term(functionAsParameter));
}

Term operator+(Expression const& expression, Constant const& constant)
{
    return createTermAddingAnExpressionAndATerm(expression, Term(constant));
}

Term operator+(Expression const& expression, Variable const& variable)
{
    return createTermAddingAnExpressionAndATerm(expression, Term(variable));
}

Term operator+(Expression const& expression, Monomial const& monomial)
{
    return createTermAddingAnExpressionAndATerm(expression, Term(monomial));
}

Term operator+(Expression const& expression, Polynomial const& polynomial)
{
    return createTermAddingAnExpressionAndATerm(expression, Term(polynomial));
}

Term operator+(Expression const& expression1, Expression const& expression2)
{
    return createTermAddingAnExpressionAndATerm(expression1, Term(expression2));
}

Term operator+(Expression const& expression, Function const& functionAsParameter)
{
    return createTermAddingAnExpressionAndATerm(expression, Term(functionAsParameter));
}

Term operator+(Function const& functionAsParameter, Constant const& constant)
{
    return createTermWithAnExpressionAdding2Terms(Term(functionAsParameter), Term(constant));
}

Term operator+(Function const& functionAsParameter, Variable const& variable)
{
    return createTermWithAnExpressionAdding2Terms(Term(functionAsParameter), Term(variable));
}

Term operator+(Function const& functionAsParameter, Monomial const& monomial)
{
    return createTermWithAnExpressionAdding2Terms(Term(functionAsParameter), Term(monomial));
}

Term operator+(Function const& functionAsParameter, Polynomial const& polynomial)
{
    return createTermWithAnExpressionAdding2Terms(Term(functionAsParameter), Term(polynomial));
}

Term operator+(Function const& functionAsParameter, Expression const& expression)
{
    return createTermWithAnExpressionAdding2Terms(Term(functionAsParameter), Term(expression));
}

Term operator+(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionAdding2Terms(Term(function1), Term(function2));
}

Term operator+(Term const& term1, Term const& term2)
{
    return performAddition(term1, term2);
}


//Subtraction: a - b

Term operator-(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() - constant2.getNumberConstReference());
}

Term operator-(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertPolynomialToSimplestTerm(
                Polynomial{
                    createMonomialFromConstant(constant),
                    Monomial(-1, {{variable.getVariableName(), 1}})
                });
}

Term operator-(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() - monomial.getConstantConstReference());
    }
    else
    {
        return simplifyAndConvertPolynomialToSimplestTerm(
                    Polynomial{
                        createMonomialFromConstant(constant),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial{createMonomialFromConstant(constant)};
    Polynomial subtrahend(polynomial);
    subtrahend.multiplyNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator-(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(constant), Term(expression));
}

Term operator-(Constant const& constant, Function const& functionAsParameter)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(constant), Term(functionAsParameter));
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
        return Term(AlbaNumber(0));
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
    return createTermWithAnExpressionSubtracting2Terms(Term(variable), Term(expression));
}

Term operator-(Variable const& variable, Function const& functionAsParameter)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(variable), Term(functionAsParameter));
}

Term operator-(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() - constant.getNumberConstReference());
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
    return createTermWithAnExpressionSubtracting2Terms(Term(monomial), Term(expression));
}

Term operator-(Monomial const& monomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(monomial), Term(functionAsParameter));
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
    return createTermWithAnExpressionSubtracting2Terms(Term(polynomial), Term(expression));
}

Term operator-(Polynomial const& polynomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(polynomial), Term(functionAsParameter));
}

Term operator-(Expression const& expression, Constant const& constant)
{
    return createTermSubtractingAnExpressionAndATerm(expression, Term(constant));
}

Term operator-(Expression const& expression, Variable const& variable)
{
    return createTermSubtractingAnExpressionAndATerm(expression, Term(variable));
}

Term operator-(Expression const& expression, Monomial const& monomial)
{
    return createTermSubtractingAnExpressionAndATerm(expression, Term(monomial));
}

Term operator-(Expression const& expression, Polynomial const& polynomial)
{
    return createTermSubtractingAnExpressionAndATerm(expression, Term(polynomial));
}

Term operator-(Expression const& expression1, Expression const& expression2)
{
    return createTermSubtractingAnExpressionAndATerm(expression1, Term(expression2));
}

Term operator-(Expression const& expression, Function const& functionAsParameter)
{
    return createTermSubtractingAnExpressionAndATerm(expression, Term(functionAsParameter));
}

Term operator-(Function const& functionAsParameter, Constant const& constant)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(functionAsParameter), Term(constant));
}

Term operator-(Function const& functionAsParameter, Variable const& variable)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(functionAsParameter), Term(variable));
}

Term operator-(Function const& functionAsParameter, Monomial const& monomial)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(functionAsParameter), Term(monomial));
}

Term operator-(Function const& functionAsParameter, Polynomial const& polynomial)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(functionAsParameter), Term(polynomial));
}

Term operator-(Function const& functionAsParameter, Expression const& expression)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(functionAsParameter), Term(expression));
}

Term operator-(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionSubtracting2Terms(Term(function1), Term(function2));
}

Term operator-(Term const& term1, Term const& term2)
{
    return performSubtraction(term1, term2);
}


//Multiplication: a * b

Term operator*(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() * constant2.getNumberConstReference());
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
    return createTermWithAnExpressionMultiplying2Terms(Term(constant), Term(expression));
}

Term operator*(Constant const& constant, Function const& functionAsParameter)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(constant), Term(functionAsParameter));
}

Term operator*(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));}

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
    return createTermWithAnExpressionMultiplying2Terms(Term(variable), Term(expression));
}

Term operator*(Variable const& variable, Function const& functionAsParameter)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(variable), Term(functionAsParameter));
}

Term operator*(Monomial const& monomial, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(                Monomial(
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
    return createTermWithAnExpressionMultiplying2Terms(Term(monomial), Term(expression));
}

Term operator*(Monomial const& monomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(monomial), Term(functionAsParameter));
}

Term operator*(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);    newPolynomial.multiplyNumber(constant.getNumberConstReference());
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

Term operator*(Polynomial const& polynomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(polynomial), Term(functionAsParameter));
}

Term operator*(Expression const& expression, Constant const& constant)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, Term(constant));}

Term operator*(Expression const& expression, Variable const& variable)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, Term(variable));
}

Term operator*(Expression const& expression, Monomial const& monomial)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, Term(monomial));
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

Term operator*(Expression const& expression, Function const& functionAsParameter)
{
    return createTermMultiplyingAnExpressionAndATerm(expression, Term(functionAsParameter));
}

Term operator*(Function const& functionAsParameter, Constant const& constant)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(functionAsParameter), Term(constant));
}

Term operator*(Function const& functionAsParameter, Variable const& variable)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(functionAsParameter), Term(variable));
}

Term operator*(Function const& functionAsParameter, Monomial const& monomial)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(functionAsParameter), Term(monomial));
}

Term operator*(Function const& functionAsParameter, Polynomial const& polynomial)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(functionAsParameter), Term(polynomial));
}

Term operator*(Function const& functionAsParameter, Expression const& expression)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(functionAsParameter), Term(expression));
}

Term operator*(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionMultiplying2Terms(Term(function1), Term(function2));
}

Term operator*(Term const& term1, Term const& term2)
{
    return performMultiplication(term1, term2);}


//Divsion: a / b

Term operator/(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() / constant2.getNumberConstReference());
}

Term operator/(Constant const& constant, Variable const& variable)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), -1}}));
}

Term operator/(Constant const& constant, Monomial const& monomial)
{
    Monomial newMonomial(createMonomialFromConstant(constant));
    newMonomial.divideMonomial(monomial);
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator/(Constant const& constant, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible({Term(constant), Term("/"), Term(polynomial)}));
}

Term operator/(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(Term(constant), Term(expression));
}

Term operator/(Constant const& constant, Function const& functionAsParameter)
{
    return createTermWithAnExpressionDividing2Terms(Term(constant), Term(functionAsParameter));
}

Term operator/(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(AlbaNumber(1)/constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));}

Term operator/(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return Term(AlbaNumber(1));
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
        return Term(AlbaNumber(1)/monomial.getConstantConstReference());
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
    return Term(createExpressionIfPossible({Term(variable), Term("/"), Term(polynomial)}));
}

Term operator/(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(Term(variable), Term(expression));
}

Term operator/(Variable const& variable, Function const& functionAsParameter)
{
    return createTermWithAnExpressionDividing2Terms(Term(variable), Term(functionAsParameter));
}

Term operator/(Monomial const& monomial, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(                Monomial(
                    monomial.getConstantConstReference()/constant.getNumberConstReference(),
                    monomial.getVariablesToExponentsMapConstReference()));
}

Term operator/(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedInAMonomialByAdditionOrSubtraction(monomial, variable))
    {
        return Term(monomial.getConstantConstReference());
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
    return Term(createExpressionIfPossible({Term(monomial), Term("/"), Term(polynomial)}));
}

Term operator/(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(Term(monomial), Term(expression));
}

Term operator/(Monomial const& monomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionDividing2Terms(Term(monomial), Term(functionAsParameter));
}

Term operator/(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);    newPolynomial.divideNumber(constant.getNumberConstReference());
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
    return Term(createExpressionIfPossible({Term(polynomial1), Term("/"), Term(polynomial2)}));
}

Term operator/(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(Term(polynomial), Term(expression));
}

Term operator/(Polynomial const& polynomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionDividing2Terms(Term(polynomial), Term(functionAsParameter));
}

Term operator/(Expression const& expression, Constant const& constant)
{
    return createTermDividingAnExpressionAndATerm(expression, Term(constant));}

Term operator/(Expression const& expression, Variable const& variable)
{
    return createTermDividingAnExpressionAndATerm(expression, Term(variable));
}

Term operator/(Expression const& expression, Monomial const& monomial)
{
    return createTermDividingAnExpressionAndATerm(expression, Term(monomial));
}

Term operator/(Expression const& expression, Polynomial const& polynomial)
{
    return createTermDividingAnExpressionAndATerm(expression, Term(polynomial));
}

Term operator/(Expression const& expression1, Expression const& expression2)
{
    return createTermDividingAnExpressionAndATerm(expression1, Term(expression2));
}

Term operator/(Expression const& expression, Function const& functionAsParameter)
{
    return createTermDividingAnExpressionAndATerm(expression, Term(functionAsParameter));
}

Term operator/(Function const& functionAsParameter, Constant const& constant)
{
    return createTermWithAnExpressionDividing2Terms(Term(functionAsParameter), Term(constant));
}

Term operator/(Function const& functionAsParameter, Variable const& variable)
{
    return createTermWithAnExpressionDividing2Terms(Term(functionAsParameter), Term(variable));
}

Term operator/(Function const& functionAsParameter, Monomial const& monomial)
{
    return createTermWithAnExpressionDividing2Terms(Term(functionAsParameter), Term(monomial));
}

Term operator/(Function const& functionAsParameter, Polynomial const& polynomial)
{
    return createTermWithAnExpressionDividing2Terms(Term(functionAsParameter), Term(polynomial));
}

Term operator/(Function const& functionAsParameter, Expression const& expression)
{
    return createTermWithAnExpressionDividing2Terms(Term(functionAsParameter), Term(expression));
}

Term operator/(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionDividing2Terms(Term(function1), Term(function2));
}

Term operator/(Term const& term1, Term const& term2)
{
    return performDivision(term1, term2);}


//RaiseToThePower: a ^ b

Term operator^(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() ^ constant2.getNumberConstReference());
}

Term operator^(Constant const& constant, Variable const& variable)
{
    return Term(createExpressionIfPossible({Term(constant), Term("^"), Term(variable)}));
}

Term operator^(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() ^ monomial.getConstantConstReference());
    }
    else
    {
        return Term(createExpressionIfPossible({Term(constant), Term("^"), Term(monomial)}));
    }
}

Term operator^(Constant const& constant, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible({Term(constant), Term("^"), Term(polynomial)}));
}

Term operator^(Constant const& constant, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(constant), Term(expression));
}

Term operator^(Constant const& constant, Function const& functionAsParameter)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(constant), Term(functionAsParameter));
}

Term operator^(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}}));}

Term operator^(Variable const& variable1, Variable const& variable2)
{
    return Term(createExpressionIfPossible({Term(variable1), Term("^"), Term(variable2)}));
}

Term operator^(Variable const& variable, Monomial const& monomial)
{
    return Term(createExpressionIfPossible({Term(variable), Term("^"), Term(monomial)}));
}

Term operator^(Variable const& variable, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible({Term(variable), Term("^"), Term(polynomial)}));
}

Term operator^(Variable const& variable, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(variable), Term(expression));
}

Term operator^(Variable const& variable, Function const& functionAsParameter)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(variable), Term(functionAsParameter));
}

Term operator^(Monomial const& monomial, Constant const& constant)
{
    Monomial newMonomial(monomial);    newMonomial.raiseToPowerNumber(constant.getNumberConstReference());
    return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
}

Term operator^(Monomial const& monomial, Variable const& variable)
{
    return Term(createExpressionIfPossible({Term(monomial), Term("^"), Term(variable)}));
}

Term operator^(Monomial const& monomial1, Monomial const& monomial2)
{
    return Term(createExpressionIfPossible({Term(monomial1), Term("^"), Term(monomial2)}));
}

Term operator^(Monomial const& monomial, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible({Term(monomial), Term("^"), Term(polynomial)}));
}

Term operator^(Monomial const& monomial, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(monomial), Term(expression));
}

Term operator^(Monomial const& monomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(monomial), Term(functionAsParameter));
}

Term operator^(Polynomial const& polynomial, Constant const& constant)
{
    Term newTerm;    AlbaNumber exponentNumber(constant.getNumberConstReference());
    if(exponentNumber.isIntegerType())
    {
        int exponentInteger(exponentNumber.getInteger());
        if(exponentInteger == 0)
        {
            newTerm = Term(Constant(1));
        }
        else
        {
            unsigned int exponentAbsoluteValue(static_cast<unsigned int>(getAbsoluteValue(exponentInteger)));
            Polynomial newPolynomial(polynomial);
            for(unsigned int exponentCount=1;  exponentCount<exponentAbsoluteValue; exponentCount++)
            {
                newPolynomial.multiplyPolynomial(polynomial);
            }
            if(exponentInteger > 0)
            {
                newTerm = simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
            }
            else
            {
                newTerm = Term(createExpressionIfPossible({Term(1), Term("/"), simplifyAndConvertPolynomialToSimplestTerm(newPolynomial)}));
            }
        }
    }
    else
    {
        newTerm = Term(createExpressionIfPossible({Term(polynomial), Term("^"), Term(constant)}));
    }
    return newTerm;
}

Term operator^(Polynomial const& polynomial, Variable const& variable)
{
    return Term(createExpressionIfPossible({Term(polynomial), Term("^"), Term(variable)}));
}

Term operator^(Polynomial const& polynomial, Monomial const& monomial)
{
    return Term(createExpressionIfPossible({Term(polynomial), Term("^"), Term(monomial)}));
}

Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    return Term(createExpressionIfPossible({Term(polynomial1), Term("^"), Term(polynomial2)}));
}

Term operator^(Polynomial const& polynomial, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(polynomial), Term(expression));
}

Term operator^(Polynomial const& polynomial, Function const& functionAsParameter)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(polynomial), Term(functionAsParameter));
}

Term operator^(Expression const& expression, Constant const& constant)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, Term(constant));}

Term operator^(Expression const& expression, Variable const& variable)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, Term(variable));
}

Term operator^(Expression const& expression, Monomial const& monomial)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, Term(monomial));
}

Term operator^(Expression const& expression, Polynomial const& polynomial)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, Term(polynomial));
}

Term operator^(Expression const& expression1, Expression const& expression2)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression1, Term(expression2));
}

Term operator^(Expression const& expression, Function const& functionAsParameter)
{
    return createTermRaisingToPowerAnExpressionAndATerm(expression, Term(functionAsParameter));
}

Term operator^(Function const& functionAsParameter, Constant const& constant)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(functionAsParameter), Term(constant));
}

Term operator^(Function const& functionAsParameter, Variable const& variable)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(functionAsParameter), Term(variable));
}

Term operator^(Function const& functionAsParameter, Monomial const& monomial)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(functionAsParameter), Term(monomial));
}

Term operator^(Function const& functionAsParameter, Polynomial const& polynomial)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(functionAsParameter), Term(polynomial));
}

Term operator^(Function const& functionAsParameter, Expression const& expression)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(functionAsParameter), Term(expression));
}

Term operator^(Function const& function1, Function const& function2)
{
    return createTermWithAnExpressionRaisingToPower2Terms(Term(function1), Term(function2));
}

Term operator^(Term const& term1, Term const& term2)
{
    return performRaiseToPower(term1, term2);}

}

}
