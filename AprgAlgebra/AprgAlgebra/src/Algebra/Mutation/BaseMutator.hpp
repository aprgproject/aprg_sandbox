#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace algebra
{

class BaseMutator
{
public:

    virtual void mutateEquation(Equation & equation) const
    {
        mutateTerm(equation.getLeftHandTermReference());
        mutateTerm(equation.getRightHandTermReference());
    }

    virtual void mutateTerm(Term & term) const
    {
        if(term.isConstant())
        {
            mutateConstant(term.getConstantReference());
        }
        else if(term.isVariable())
        {
            mutateVariable(term.getVariableReference());
        }
        else if(term.isMonomial())
        {
            mutateMonomial(term.getMonomialReference());
        }
        else if(term.isPolynomial())
        {
            mutatePolynomial(term.getPolynomialReference());
        }
        else if(term.isExpression())
        {
            mutateExpression(term.getExpressionReference());
        }
        else if(term.isFunction())
        {
            mutateFunction(term.getFunctionReference());
        }
    }

    virtual void mutateConstant(Constant &) const
    {}

    virtual void mutateVariable(Variable &) const
    {}

    virtual void mutateMonomial(Monomial &) const
    {}

    virtual void mutatePolynomial(Polynomial & polynomial) const
    {
        for(Monomial & monomial : polynomial.getMonomialsReference())
        {
            mutateMonomial(monomial);
        }
    }

    virtual void mutateExpression(Expression & expression) const
    {
        for(TermWithDetails & termWithDetails
            : expression.getTermsWithAssociationReference().getTermsWithDetailsReference())
        {
            mutateTerm(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        }
    }

    virtual void mutateFunction(Function & functionObject) const
    {
        mutateTerm(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
    }
};

}

}
