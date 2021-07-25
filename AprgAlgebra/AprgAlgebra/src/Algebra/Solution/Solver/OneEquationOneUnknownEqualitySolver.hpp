#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

class OneEquationOneUnknownEqualitySolver
{
public:
    OneEquationOneUnknownEqualitySolver(Equation const& equation);

private:
    Equation m_equation;
};


}

}
