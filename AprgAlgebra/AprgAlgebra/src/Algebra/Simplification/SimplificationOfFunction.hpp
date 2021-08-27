#pragma once

#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationOfFunction
{
public:
    SimplificationOfFunction(Function const& functionObject);

    Function getFunction() const;

    void simplify();

private:
    bool isNegatedTermSimpler(Term const& term,  Term const& negatedTerm) const;
    Function m_function;
};

}

}

}
