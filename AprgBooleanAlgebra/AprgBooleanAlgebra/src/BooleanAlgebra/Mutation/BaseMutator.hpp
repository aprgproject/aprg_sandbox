#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

class BaseMutator
{
public:
    virtual void mutateTerm(Term & term);
    virtual void mutateConstant(Constant &);
    virtual void mutateVariableTerm(VariableTerm &);
    virtual void mutateExpression(Expression & expression);
};

}

}
