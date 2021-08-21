#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

namespace Simplification
{

class SimplificationOfEquation
{
public:
    SimplificationOfEquation(Equation const& equation);

    Equation getEquation() const;

    void simplify();

private:
    Expression getNewCombinedExpression(Equation const& equation) const;

    Equation m_equation;
};

}

}

}
