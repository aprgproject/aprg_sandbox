#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

class BaseMutator
{
public:
    virtual void mutateEquation(Equation & equation);
    virtual void mutateTerm(Term & term);
    virtual void mutateConstant(Constant &);
    virtual void mutateVariable(Variable &);
    virtual void mutateMonomial(Monomial &);
    virtual void mutatePolynomial(Polynomial & polynomial);
    virtual void mutateExpression(Expression & expression);
    virtual void mutateFunction(Function & functionObject);
};

}

}
