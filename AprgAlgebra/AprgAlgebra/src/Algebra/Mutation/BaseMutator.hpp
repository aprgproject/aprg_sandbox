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

    virtual void mutateEquation(Equation & equation)
    {
        mutateTerm(equation.getLeftHandTermReference());
        mutateTerm(equation.getRightHandTermReference());
    }

    virtual void mutateTerm(Term & term)
    {
        if(term.isConstant())
        {            mutateConstant(term.getConstantReference());
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

    virtual void mutateConstant(Constant &)
    {}

    virtual void mutateVariable(Variable &)
    {}

    virtual void mutateMonomial(Monomial &)
    {}

    virtual void mutatePolynomial(Polynomial & polynomial)
    {
        for(Monomial & monomial : polynomial.getMonomialsReference())
        {            mutateMonomial(monomial);
        }
    }

    virtual void mutateExpression(Expression & expression)
    {
        for(TermWithDetails & termWithDetails
            : expression.getTermsWithAssociationReference().getTermsWithDetailsReference())        {
            mutateTerm(getTermReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        }
    }

    virtual void mutateFunction(Function & functionObject)
    {
        mutateTerm(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
    }};

}

}
