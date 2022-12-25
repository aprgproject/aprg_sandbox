#include "BaseMutator.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace booleanAlgebra
{

void BaseMutator::mutateTerm(Term & term)
{
    if(term.isConstant())
    {
        mutateConstant(term.getConstantReference());
    }
    else if(term.isVariableTerm())
    {
        mutateVariableTerm(term.getVariableTermReference());
    }
    else if(term.isExpression())
    {
        mutateExpression(term.getExpressionReference());
    }
}

void BaseMutator::mutateConstant(Constant &)
{}

void BaseMutator::mutateVariableTerm(VariableTerm &)
{}

void BaseMutator::mutateExpression(Expression & expression)
{
    for(WrappedTerm & wrappedTerm : expression.getWrappedTermsReference())
    {
        mutateTerm(getTermReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
    }
}
}

}