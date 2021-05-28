#include "Utilities.hpp"

using namespace std;

namespace alba
{

namespace equation
{

bool isOperator(string const& variableOrOperator)
{
    return "+" == variableOrOperator ||
            "-" == variableOrOperator ||
            "*" == variableOrOperator ||
            "/" == variableOrOperator;
}

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms)
{
    WrappedTerms::BaseTermPointers & baseTermPointers(wrappedTerms.getBaseTermPointersReference());
    for(Term const& term : terms)
    {
        baseTermPointers.emplace_back(new Term(term));
    }
}

Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms)
{
    WrappedTerms::BaseTermPointers const& baseTermPointers(wrappedTerms.getBaseTermPointersConstReference());
    Terms result;
    for(std::shared_ptr<BaseTerm> const& baseTermPointer : baseTermPointers)
    {
        Term const& term(*dynamic_cast<Term const * const>(baseTermPointer.get()));
        result.emplace_back(term);
    }
    return result;
}

Expression createExpression(Terms const& terms)
{
    Expression result;
    wrapTerms(result.getWrappedTermsReference(), terms);
    return result;
}

Terms getTermsInAnExpression(Expression const& expression)
{
    return unwrapTermsAndReturnTerms(expression.getWrappedTermsConstReference());
}

}

}