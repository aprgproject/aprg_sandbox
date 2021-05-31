#include "Expression.hpp"

#include <Term.hpp>
#include <Utilities.hpp>

namespace alba
{

namespace equation
{

Expression::Expression()
{}

Expression::~Expression()
{}

bool Expression::isMultipleTermsExpression() const
{
    bool isMultipleTerms(false);
    Terms terms(unwrapTermsAndReturnTerms(m_wrappedTerms));
    for(Term const& term : terms)
    {
        if(TermType::ExpressionWithMutipleTerms == term.getTermType())
        {
            isMultipleTerms = true;
        }
        else if(TermType::Operator == term.getTermType())
        {
            if(isOperatorForMultipleTerms(term.getOperatorConstReference().getOperatorString()))
            {
                isMultipleTerms = true;
            }
        }
    }
    return isMultipleTerms;
}

TermType Expression::getTermTypeForExpression() const
{
    TermType result(TermType::ExpressionWithSingleTerm);
    if(isMultipleTermsExpression())
    {
        result = TermType::ExpressionWithMutipleTerms;
    }
    return result;
}

WrappedTerms & Expression::getWrappedTermsReference()
{
    return m_wrappedTerms;
}

WrappedTerms const& Expression::getWrappedTermsConstReference() const
{
    return m_wrappedTerms;
}

}

}
