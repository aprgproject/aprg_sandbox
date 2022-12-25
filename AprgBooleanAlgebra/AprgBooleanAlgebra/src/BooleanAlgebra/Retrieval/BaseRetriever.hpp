#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>
#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace booleanAlgebra
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

    virtual void retrieveFromTerm(Term const& term)
    {
        if(term.isConstant())
        {
            retrieveFromConstant(term.getConstantConstReference());
        }
        else if(term.isVariableTerm())
        {
            retrieveFromVariableTerm(term.getVariableTermConstReference());
        }
        else if(term.isExpression())
        {
            retrieveFromExpression(term.getExpressionConstReference());
        }
    }

    virtual void retrieveFromConstant(Constant const&)
    {}

    virtual void retrieveFromVariableTerm(VariableTerm const&)
    {}

    virtual void retrieveFromExpression(Expression const& expression)
    {
        for(WrappedTerm const& wrappedTerm : expression.getWrappedTerms())
        {
            retrieveFromTerm(getTermConstReferenceFromSharedPointer(wrappedTerm.baseTermSharedPointer));
        }
    }
protected:

    DataType m_savedData;};

}

}
