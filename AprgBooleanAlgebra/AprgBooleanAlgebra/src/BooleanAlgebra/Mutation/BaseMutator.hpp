#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

class BaseMutator
{
public:
    virtual ~BaseMutator() = default; // virtual destructor because of virtual functions (vtable exists)

    virtual void mutateTerm(Term & term);
    virtual void mutateConstant(Constant &);    virtual void mutateVariableTerm(VariableTerm &);
    virtual void mutateExpression(Expression & expression);
};
}

}
