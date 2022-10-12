#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace algebra
{

template <typename DataType>
class BaseRetriever
{
public:
    virtual ~BaseRetriever() = default;

    DataType const& getSavedData() const
    {
        return m_savedData;
    }

    DataType & getSavedDataReference()
    {
        return m_savedData;
    }

    virtual void retrieveFromEquations(Equations const& equations)
    {
        for(Equation const& equation : equations)
        {
            retrieveFromEquation(equation);
        }
    }

    virtual void retrieveFromEquation(Equation const& equation)
    {
        retrieveFromTerm(equation.getLeftHandTerm());
        retrieveFromTerm(equation.getRightHandTerm());
    }

    virtual void retrieveFromTerm(Term const& term)
    {
        if(term.isConstant())
        {
            retrieveFromConstant(term.getConstantConstReference());
        }
        else if(term.isVariable())
        {
            retrieveFromVariable(term.getVariableConstReference());
        }
        else if(term.isMonomial())
        {
            retrieveFromMonomial(term.getMonomialConstReference());
        }
        else if(term.isPolynomial())
        {
            retrieveFromPolynomial(term.getPolynomialConstReference());
        }
        else if(term.isExpression())
        {
            retrieveFromExpression(term.getExpressionConstReference());
        }
        else if(term.isFunction())
        {
            retrieveFromFunction(term.getFunctionConstReference());
        }
    }

    virtual void retrieveFromConstant(Constant const&)
    {}

    virtual void retrieveFromVariable(Variable const&)
    {}

    virtual void retrieveFromMonomial(Monomial const&)
    {}

    virtual void retrieveFromPolynomial(Polynomial const& polynomial)
    {
        for(Monomial const& monomial : polynomial.getMonomialsConstReference())
        {
            retrieveFromMonomial(monomial);
        }
    }

    virtual void retrieveFromExpression(Expression const& expression)
    {
        for(TermWithDetails const& termWithDetails
            : expression.getTermsWithAssociation().getTermsWithDetails())
        {
            retrieveFromTerm(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        }
    }

    virtual void retrieveFromFunction(Function const& functionObject)
    {
        retrieveFromTerm(getTermConstReferenceFromBaseTerm(functionObject.getInputTermConstReference()));
    }

    virtual void retrieveFromPolynomials(Polynomials const& polynomials)
    {
        for(Polynomial const& polynomial : polynomials)
        {
            retrieveFromPolynomial(polynomial);
        }
    }

protected:

    DataType m_savedData;
};

}

}
