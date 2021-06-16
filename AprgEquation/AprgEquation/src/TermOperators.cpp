#include "TermOperators.hpp"

#include <Math/AlbaMathHelper.hpp>
#include <PerformOperations.hpp>
#include <Utilities.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

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
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(-1)));
    return Term(newExpression);
}
Term operator-(Term const& term)
{
    return performUnaryMinus(term);}


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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(constant)));
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertPolynomialToSimplestTerm(                Polynomial{
                    createMonomialFromVariable(variable),
                    createMonomialFromConstant(constant)
                });
}

Term operator+(Variable const& variable1, Variable const& variable2)
{
    if(canBeMergedByAdditionOrSubtraction(variable1, variable2))
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(variable)));
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())    {
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    if(canBeMergedByAdditionOrSubtraction(monomial1, monomial2))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(monomial)));
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);    newPolynomial.addMonomial(createMonomialFromConstant(constant));
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Expression const& expression, Constant const& constant)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(constant)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Expression const& expression, Variable const& variable)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(variable)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Expression const& expression, Monomial const& monomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putTermWithAdditionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression2)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator+(Term const& term1, Term const& term2)
{
    return performAddition(term1, term2);}


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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(constant)));
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertPolynomialToSimplestTerm(                Polynomial{
                    createMonomialFromVariable(variable),
                    Monomial(constant.getNumberConstReference()*-1, {})
                });
}

Term operator-(Variable const& variable1, Variable const& variable2)
{
    if(canBeMergedByAdditionOrSubtraction(variable1, variable2))
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(variable)));
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())    {
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    if(canBeMergedByAdditionOrSubtraction(monomial1, monomial2))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(monomial)));
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference()*-1, {}));
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Expression const& expression, Constant const& constant)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(constant)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Expression const& expression, Variable const& variable)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(variable)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Expression const& expression, Monomial const& monomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putTermWithSubtractionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression2)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator-(Term const& term1, Term const& term2)
{
    return performSubtraction(term1, term2);}


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
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() * monomial.getConstantConstReference());
    }
    else
    {
        return simplifyAndConvertMonomialToSimplestTerm(
                    Monomial(
                        constant.getNumberConstReference()*monomial.getConstantConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyNumber(constant.getNumberConstReference());
    return simplifyAndConvertPolynomialToSimplestTerm(newPolynomial);
}

Term operator*(Constant const& constant, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(constant)));
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(variable)));
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator*(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())    {
        return Term(monomial.getConstantConstReference() * constant.getNumberConstReference());
    }
    else
    {
        return simplifyAndConvertMonomialToSimplestTerm(
                    Monomial(
                        monomial.getConstantConstReference()*constant.getNumberConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(monomial)));
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
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

Term operator*(Expression const& expression, Constant const& constant)
{
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(constant)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator*(Expression const& expression, Variable const& variable)
{
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(variable)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator*(Expression const& expression, Monomial const& monomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator*(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);    newExpression.putPolynomialSecondWithMultiplication(polynomial);
    return convertExpressionToSimplestTerm(newExpression);
}

Term operator*(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putExpressionWithMultiplication(expression2);
    return convertExpressionToSimplestTerm(newExpression);
}

Term operator*(Term const& term1, Term const& term2)
{
    return performMultiplication(term1, term2);
}


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
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() / monomial.getConstantConstReference());
    }
    else
    {
        Monomial newMonomial(createMonomialFromConstant(constant));
        newMonomial.divideMonomial(monomial);
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator/(Constant const& constant, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible(Terms{Term(constant), Term("/"), Term(polynomial)}));
}

Term operator/(Constant const& constant, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(constant)));
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
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
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    return Term(createExpressionIfPossible(Terms{Term(variable), Term("/"), Term(polynomial)}));
}

Term operator/(Variable const& variable, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(variable)));
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())    {
        return Term(monomial.getConstantConstReference() / constant.getNumberConstReference());
    }
    else
    {
        return simplifyAndConvertMonomialToSimplestTerm(
                    Monomial(
                        monomial.getConstantConstReference()/constant.getNumberConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator/(Monomial const& monomial, Variable const& variable)
{
    if(canBeMergedByAdditionOrSubtraction(monomial, variable))
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
    return Term(createExpressionIfPossible(Terms{Term(monomial), Term("/"), Term(polynomial)}));
}

Term operator/(Monomial const& monomial, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(monomial)));
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
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
    return Term(createExpressionIfPossible(Terms{Term(polynomial1), Term("/"), Term(polynomial2)}));
}

Term operator/(Polynomial const& polynomial, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Expression const& expression, Constant const& constant)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(constant)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Expression const& expression, Variable const& variable)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(variable)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Expression const& expression, Monomial const& monomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator/(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putTermWithDivisionIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression2)));
    return convertExpressionToSimplestTerm(newExpression);
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
    return Term(createExpressionIfPossible(Terms{Term(constant), Term("^"), Term(variable)}));
}

Term operator^(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() ^ monomial.getConstantConstReference());
    }
    else
    {
        return Term(createExpressionIfPossible(Terms{Term(constant), Term("^"), Term(monomial)}));
    }
}

Term operator^(Constant const& constant, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible(Terms{Term(constant), Term("^"), Term(polynomial)}));
}

Term operator^(Constant const& constant, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(constant)));
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Variable const& variable, Constant const& constant)
{
    return simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}}));}

Term operator^(Variable const& variable1, Variable const& variable2)
{
    return Term(createExpressionIfPossible(Terms{Term(variable1), Term("^"), Term(variable2)}));
}

Term operator^(Variable const& variable, Monomial const& monomial)
{
    return Term(createExpressionIfPossible(Terms{Term(variable), Term("^"), Term(monomial)}));
}

Term operator^(Variable const& variable, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible(Terms{Term(variable), Term("^"), Term(polynomial)}));
}

Term operator^(Variable const& variable, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(variable)));
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())    {
        return Term(monomial.getConstantConstReference() ^ constant.getNumberConstReference());
    }
    else
    {
        Monomial newMonomial(monomial);
        newMonomial.raiseToPowerNumber(constant.getNumberConstReference());
        return simplifyAndConvertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator^(Monomial const& monomial, Variable const& variable)
{
    return Term(createExpressionIfPossible(Terms{Term(monomial), Term("^"), Term(variable)}));
}

Term operator^(Monomial const& monomial1, Monomial const& monomial2)
{
    return Term(createExpressionIfPossible(Terms{Term(monomial1), Term("^"), Term(monomial2)}));
}

Term operator^(Monomial const& monomial, Polynomial const& polynomial)
{
    return Term(createExpressionIfPossible(Terms{Term(monomial), Term("^"), Term(polynomial)}));
}

Term operator^(Monomial const& monomial, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(monomial)));
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
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
                newTerm = Term(createExpressionIfPossible(Terms{Term(1), Term("/"), simplifyAndConvertPolynomialToSimplestTerm(newPolynomial)}));
            }
        }
    }
    else
    {
        newTerm = Term(createExpressionIfPossible(Terms{Term(polynomial), Term("^"), Term(constant)}));
    }
    return newTerm;
}

Term operator^(Polynomial const& polynomial, Variable const& variable)
{
    return Term(createExpressionIfPossible(Terms{Term(polynomial), Term("^"), Term(variable)}));
}

Term operator^(Polynomial const& polynomial, Monomial const& monomial)
{
    return Term(createExpressionIfPossible(Terms{Term(polynomial), Term("^"), Term(monomial)}));
}

Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    return Term(createExpressionIfPossible(Terms{Term(polynomial1), Term("^"), Term(polynomial2)}));
}

Term operator^(Polynomial const& polynomial, Expression const& expression)
{
    Expression newExpression(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Expression const& expression, Constant const& constant)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(constant)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Expression const& expression, Variable const& variable)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(variable)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Expression const& expression, Monomial const& monomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(monomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Expression const& expression, Polynomial const& polynomial)
{
    Expression newExpression(expression);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(polynomial)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Expression const& expression1, Expression const& expression2)
{
    Expression newExpression(expression1);
    newExpression.putTermWithRaiseToPowerIfNeeded(getBaseTermConstReferenceFromTerm(Term(expression2)));
    return convertExpressionToSimplestTerm(newExpression);
}
Term operator^(Term const& term1, Term const& term2)
{
    return performRaiseToPower(term1, term2);}

}

}
