#pragma once

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
    Function m_function;
};

}

}

}
