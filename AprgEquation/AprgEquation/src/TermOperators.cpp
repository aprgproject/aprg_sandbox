#include "TermOperators.hpp"

#include <Utilities.hpp>

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


//Unary minus: -a

Term operator-(Constant const& constant)
{
    return Term(-constant.getNumberConstReference());
}

Term operator-(Variable const& variable)
{
    return convertMonomialToSimplestTerm(Monomial(-1, {{variable.getVariableName(), 1}}));
}

Term operator-(Monomial const& monomial)
{
    return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference()));
}

Term operator-(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(-1);
    return Term(newPolynomial);
}


//Addition: a + b

Term operator+(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() + constant2.getNumberConstReference());
}

Term operator+(Constant const& constant, Variable const& variable)
{
    return Term(Polynomial{
                    Monomial(constant.getNumberConstReference(), {}),
                    Monomial(1, {{variable.getVariableName(), 1}})
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
        return Term(Polynomial{
                        Monomial(constant.getNumberConstReference(), {}),
                        monomial
                    });
    }
}

Term operator+(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference(), {}));
    return Term(newPolynomial);
}

Term operator+(Variable const& variable, Constant const& constant)
{
    return Term(Polynomial{
                    Monomial(1, {{variable.getVariableName(), 1}}),
                    Monomial(constant.getNumberConstReference(), {})
                });
}

Term operator+(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return convertMonomialToSimplestTerm(Monomial(2, {{variable1.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable1.getVariableName(), 1}}),
                        Monomial(1, {{variable2.getVariableName(), 1}})
                    });
    }
}

Term operator+(Variable const& variable, Monomial const& monomial)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable.getVariableName(), 1}}),
                        monomial
                    });
    }
}

Term operator+(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator+(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() + constant.getNumberConstReference());
    }
    else
    {
        return Term(Polynomial{
                        monomial,
                        Monomial(constant.getNumberConstReference(), {})
                    });
    }
}

Term operator+(Monomial const& monomial, Variable const& variable)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        monomial,
                        Monomial(1, {{variable.getVariableName(), 1}})
                    });
    }
}

Term operator+(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        return convertMonomialToSimplestTerm(
                    Monomial(
                        monomial1.getConstantConstReference()+monomial2.getConstantConstReference(),
                        monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return Term(Polynomial{monomial1, monomial2});
    }
}

Term operator+(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(monomial);
    return Term(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference(), {}));
    return Term(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator+(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(monomial);
    return Term(newPolynomial);
}

Term operator+(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    newPolynomial.addPolynomial(polynomial2);
    return Term(newPolynomial);
}


//Subtraction: a - b

Term operator-(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() - constant2.getNumberConstReference());
}

Term operator-(Constant const& constant, Variable const& variable)
{
    return Term(Polynomial{
                    Monomial(constant.getNumberConstReference(), {}),
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
        return Term(Polynomial{
                        Monomial(constant.getNumberConstReference(), {}),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(-1);
    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference(), {}));
    return Term(newPolynomial);
}

Term operator-(Variable const& variable, Constant const& constant)
{
    return Term(Polynomial{
                    Monomial(1, {{variable.getVariableName(), 1}}),
                    Monomial(constant.getNumberConstReference()*-1, {})
                });
}

Term operator-(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return Term(AlbaNumber(0));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable1.getVariableName(), 1}}),
                        Monomial(-1, {{variable2.getVariableName(), 1}})
                    });
    }
}

Term operator-(Variable const& variable, Monomial const& monomial)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(AlbaNumber(1)-monomial.getConstantConstReference(), {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable.getVariableName(), 1}}),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(-1);
    newPolynomial.addMonomial(Monomial(1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator-(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() - constant.getNumberConstReference());
    }
    else
    {
        return Term(Polynomial{
                        monomial,
                        Monomial(constant.getNumberConstReference()*-1, {})
                    });
    }
}

Term operator-(Monomial const& monomial, Variable const& variable)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()-1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        monomial,
                        Monomial(-1, {{variable.getVariableName(), 1}})
                    });
    }
}

Term operator-(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        return convertMonomialToSimplestTerm(
                    Monomial(
                        monomial1.getConstantConstReference()-monomial2.getConstantConstReference(),
                        monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return Term(Polynomial{
                        monomial1,
                        Monomial(monomial2.getConstantConstReference()*-1, monomial2.getVariablesToExponentsMapConstReference())
                    });
    }
}

Term operator-(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(-1);
    newPolynomial.addMonomial(monomial);
    return Term(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(constant.getNumberConstReference()*-1, {}));
    return Term(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(-1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator-(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.addMonomial(Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference()));
    return Term(newPolynomial);
}

Term operator-(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    Polynomial subtrahend(polynomial2);
    subtrahend.multiplyByNumber(-1);
    newPolynomial.addPolynomial(subtrahend);
    return Term(newPolynomial);
}


//Multiplication: a * b

Term operator*(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() * constant2.getNumberConstReference());
}

Term operator*(Constant const& constant, Variable const& variable)
{
    return convertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() * monomial.getConstantConstReference());
    }
    else
    {
        return convertMonomialToSimplestTerm(
                    Monomial(
                        constant.getNumberConstReference()*monomial.getConstantConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Constant const& constant, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(constant.getNumberConstReference());
    return Term(newPolynomial);
}

Term operator*(Variable const& variable, Constant const& constant)
{
    return convertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return convertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 2}}));
    }
    else
    {
        return convertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), 1}}));
    }
}

Term operator*(Variable const& variable, Monomial const& monomial)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        return convertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator*(Variable const& variable, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByMonomial(Monomial(1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator*(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() * constant.getNumberConstReference());
    }
    else
    {
        return convertMonomialToSimplestTerm(
                    Monomial(
                        monomial.getConstantConstReference()*constant.getNumberConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Monomial const& monomial, Variable const& variable)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        return convertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator*(Monomial const& monomial1, Monomial const& monomial2)
{
    return Term(multiplyMonomials(monomial1, monomial2));
}

Term operator*(Monomial const& monomial, Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByMonomial(monomial);
    return Term(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Constant const& constant)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByNumber(constant.getNumberConstReference());
    return Term(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Variable const& variable)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByMonomial(Monomial(1, {{variable.getVariableName(), 1}}));
    return Term(newPolynomial);
}

Term operator*(Polynomial const& polynomial, Monomial const& monomial)
{
    Polynomial newPolynomial(polynomial);
    newPolynomial.multiplyByMonomial(monomial);
    return Term(newPolynomial);
}

Term operator*(Polynomial const& polynomial1, Polynomial const& polynomial2)
{
    Polynomial newPolynomial(polynomial1);
    newPolynomial.multiplyByPolynomial(polynomial2);
    return Term(newPolynomial);
}


//Divsion: a / b

Term operator/(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() / constant2.getNumberConstReference());
}

Term operator/(Constant const& constant, Variable const& variable)
{
    return convertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), -1}}));
}

Term operator/(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() / monomial.getConstantConstReference());
    }
    else
    {
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [&constant](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*-1;
        });
        return convertMonomialToSimplestTerm(Monomial(constant.getNumberConstReference()/monomial.getConstantConstReference(), variablesMap));
    }
}

Term operator/(Constant const& constant, Polynomial const& polynomial)
{

}

Term operator/(Variable const& variable, Constant const& constant)
{
    return convertMonomialToSimplestTerm(Monomial(AlbaNumber(1)/constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator/(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return Term(AlbaNumber(1));
    }
    else
    {
        return convertMonomialToSimplestTerm(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), -1}}));
    }
}

Term operator/(Variable const& variable, Monomial const& monomial)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return Term(AlbaNumber(1)/monomial.getConstantConstReference());
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*-1;
        });
        variablesMap[variableName]=variablesMap[variableName]+1;
        return convertMonomialToSimplestTerm(Monomial(AlbaNumber(1)/monomial.getConstantConstReference(), variablesMap));
    }
}

Term operator/(Variable const& variable, Polynomial const& polynomial)
{

}

Term operator/(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() / constant.getNumberConstReference());
    }
    else
    {
        return convertMonomialToSimplestTerm(
                    Monomial(
                        monomial.getConstantConstReference()/constant.getNumberConstReference(),
                        monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator/(Monomial const& monomial, Variable const& variable)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return Term(monomial.getConstantConstReference());
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]-1;
        return convertMonomialToSimplestTerm(newMonomial);
    }
}

Term operator/(Monomial const& monomial1, Monomial const& monomial2)
{
    return convertMonomialToSimplestTerm(divideMonomials(monomial1, monomial2));
}

Term operator/(Monomial const& monomial, Polynomial const& polynomial)
{

}

Term operator/(Polynomial const& polynomial, Constant const& constant)
{

}

Term operator/(Polynomial const& polynomial, Variable const& variable)
{

}

Term operator/(Polynomial const& polynomial, Monomial const& monomial)
{

}

Term operator/(Polynomial const& polynomial1, Polynomial const& polynomial2)
{

}


//RaiseToThePower: a ^ b

Term operator^(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() ^ constant2.getNumberConstReference());
}

Term operator^(Constant const& constant, Variable const& variable)
{
    return Term(createExpression(Terms{Term(constant), Term("^"), Term(variable)}));
}

Term operator^(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() ^ monomial.getConstantConstReference());
    }
    else
    {
        return Term(createExpression(Terms{Term(constant), Term("^"), Term(monomial)}));
    }
}

Term operator^(Constant const& constant, Polynomial const& polynomial)
{

}

Term operator^(Variable const& variable, Constant const& constant)
{
    return convertMonomialToSimplestTerm(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}}));
}

Term operator^(Variable const& variable1, Variable const& variable2)
{
    return Term(createExpression(Terms{Term(variable1), Term("^"), Term(variable2)}));
}

Term operator^(Variable const& variable, Monomial const& monomial)
{
    return Term(createExpression(Terms{Term(variable), Term("^"), Term(monomial)}));
}

Term operator^(Variable const& variable, Polynomial const& polynomial)
{

}

Term operator^(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() ^ constant.getNumberConstReference());
    }
    else
    {
        Monomial::VariablesToExponentsMap variablesMap(monomial.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [&constant](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*constant.getNumberConstReference();
        });
        return convertMonomialToSimplestTerm(Monomial(monomial.getConstantConstReference()^constant.getNumberConstReference(), variablesMap));
    }
}

Term operator^(Monomial const& monomial, Variable const& variable)
{
    return Term(createExpression(Terms{Term(monomial), Term("^"), Term(variable)}));
}

Term operator^(Monomial const& monomial1, Monomial const& monomial2)
{
    return Term(createExpression(Terms{Term(monomial1), Term("^"), Term(monomial2)}));
}

Term operator^(Monomial const& monomial, Polynomial const& polynomial)
{

}

Term operator^(Polynomial const& polynomial, Constant const& constant)
{

}

Term operator^(Polynomial const& polynomial, Variable const& variable)
{

}

Term operator^(Polynomial const& polynomial, Monomial const& monomial)
{

}

Term operator^(Polynomial const& polynomial1, Polynomial const& polynomial2)
{

}


}

}
