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
    return Term(Monomial(-1, {{variable.getVariableName(), 1}}));
}

Term operator-(Monomial const& monomial)
{
    return Term(Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference()));
}

Term operator-(Polynomial const& polynomial)
{
    Polynomial newPolynomial(polynomial);
    for(Monomial & monomial : newPolynomial.getMonomialsReference())
    {
        monomial.setConstant(monomial.getConstantConstReference()*-1);
    }
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
        return Term(Monomial(2, {{variable1.getVariableName(), 1}}));
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
        return Term(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable.getVariableName(), 1}}),
                        monomial
                    });
    }
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
        return Term(Monomial(monomial.getConstantConstReference()+1, {{variable.getVariableName(), 1}}));
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
        return Term(Monomial(monomial1.getConstantConstReference()+monomial2.getConstantConstReference(), monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return Term(Polynomial{monomial1, monomial2});
    }
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
        return Term(Monomial(AlbaNumber(1)-monomial.getConstantConstReference(), {{variable.getVariableName(), 1}}));
    }
    else
    {
        return Term(Polynomial{
                        Monomial(1, {{variable.getVariableName(), 1}}),
                        Monomial(monomial.getConstantConstReference()*-1, monomial.getVariablesToExponentsMapConstReference())
                    });
    }
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
        return Term(Monomial(monomial.getConstantConstReference()-1, {{variable.getVariableName(), 1}}));
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
        return Term(Monomial(monomial1.getConstantConstReference()-monomial2.getConstantConstReference(), monomial1.getVariablesToExponentsMapConstReference()));
    }
    else
    {
        return Term(Polynomial{
                        monomial1,
                        Monomial(monomial2.getConstantConstReference()*-1, monomial2.getVariablesToExponentsMapConstReference())
                    });
    }
}


//Multiplication: a * b

Term operator*(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() * constant2.getNumberConstReference());
}

Term operator*(Constant const& constant, Variable const& variable)
{
    return Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Constant const& constant, Monomial const& monomial)
{
    if(monomial.isConstantOnly())
    {
        return Term(constant.getNumberConstReference() * monomial.getConstantConstReference());
    }
    else
    {
        return Term(Monomial(constant.getNumberConstReference()*monomial.getConstantConstReference(), monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Variable const& variable, Constant const& constant)
{
    return Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator*(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return Term(Monomial(1, {{variable1.getVariableName(), 2}}));
    }
    else
    {
        return Term(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), 1}}));
    }
}

Term operator*(Variable const& variable, Monomial const& monomial)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return Term(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        return Term(newMonomial);
    }
}

Term operator*(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() * constant.getNumberConstReference());
    }
    else
    {
        return Term(Monomial(monomial.getConstantConstReference()*constant.getNumberConstReference(), monomial.getVariablesToExponentsMapConstReference()));
    }
}

Term operator*(Monomial const& monomial, Variable const& variable)
{
    if(canBeAddedOrSubtracted(monomial, variable))
    {
        return Term(Monomial(monomial.getConstantConstReference(), {{variable.getVariableName(), 2}}));
    }
    else
    {
        string variableName(variable.getVariableName());
        Monomial newMonomial(monomial);
        Monomial::VariablesToExponentsMap & variablesMap(newMonomial.getVariablesToExponentsMapReference());
        variablesMap[variableName]=variablesMap[variableName]+1;
        return Term(newMonomial);
    }
}

Term operator*(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        Monomial::VariablesToExponentsMap variablesMap(monomial1.getVariablesToExponentsMapConstReference());
        performChangeForVariables(variablesMap, [](string const &, AlbaNumber & exponent)
        {
            exponent=exponent*2;
        });
        return Term(Monomial(monomial1.getConstantConstReference()*monomial2.getConstantConstReference(), variablesMap));
    }
    else
    {
        Monomial::VariablesToExponentsMap newVariablesMap(
                    combineVariableExponentMapByMultiplication(
                        monomial1.getVariablesToExponentsMapConstReference(),
                        monomial2.getVariablesToExponentsMapConstReference()));
        return Term(Monomial(monomial1.getConstantConstReference()*monomial2.getConstantConstReference(), newVariablesMap));
    }
}


//Divsion: a / b

Term operator/(Constant const& constant1, Constant const& constant2)
{
    return Term(constant1.getNumberConstReference() / constant2.getNumberConstReference());
}

Term operator/(Constant const& constant, Variable const& variable)
{
    return Term(Monomial(constant.getNumberConstReference(), {{variable.getVariableName(), -1}}));
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
        return Term(Monomial(constant.getNumberConstReference()/monomial.getConstantConstReference(), variablesMap));
    }
}

Term operator/(Variable const& variable, Constant const& constant)
{
    return Term(Monomial(AlbaNumber(1)/constant.getNumberConstReference(), {{variable.getVariableName(), 1}}));
}

Term operator/(Variable const& variable1, Variable const& variable2)
{
    if(variable1.getVariableName() == variable2.getVariableName())
    {
        return Term(AlbaNumber(1));
    }
    else
    {
        return Term(Monomial(1, {{variable1.getVariableName(), 1}, {variable2.getVariableName(), -1}}));
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
        return Term(Monomial(AlbaNumber(1)/monomial.getConstantConstReference(), variablesMap));
    }
}

Term operator/(Monomial const& monomial, Constant const& constant)
{
    if(monomial.isConstantOnly())
    {
        return Term(monomial.getConstantConstReference() / constant.getNumberConstReference());
    }
    else
    {
        return Term(Monomial(monomial.getConstantConstReference()/constant.getNumberConstReference(), monomial.getVariablesToExponentsMapConstReference()));
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
        return Term(newMonomial);
    }
}

Term operator/(Monomial const& monomial1, Monomial const& monomial2)
{
    if(canBeAddedOrSubtracted(monomial1, monomial2))
    {
        return Term(monomial1.getConstantConstReference()/monomial2.getConstantConstReference());
    }
    else
    {
        Monomial::VariablesToExponentsMap newVariablesMap(
                    combineVariableExponentMapByDivision(
                        monomial1.getVariablesToExponentsMapConstReference(),
                        monomial2.getVariablesToExponentsMapConstReference()));
        return Term(Monomial(monomial1.getConstantConstReference()/monomial2.getConstantConstReference(), newVariablesMap));
    }
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

Term operator^(Variable const& variable, Constant const& constant)
{
    return Term(Monomial(1, {{variable.getVariableName(), constant.getNumberConstReference()}}));
}

Term operator^(Variable const& variable1, Variable const& variable2)
{
    return Term(createExpression(Terms{Term(variable1), Term("^"), Term(variable2)}));
}

Term operator^(Variable const& variable, Monomial const& monomial)
{
    return Term(createExpression(Terms{Term(variable), Term("^"), Term(monomial)}));
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
        return Term(Monomial(monomial.getConstantConstReference()^constant.getNumberConstReference(), variablesMap));
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


}

}
