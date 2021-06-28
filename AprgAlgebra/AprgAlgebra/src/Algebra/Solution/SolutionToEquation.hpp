#pragma once

#include <Algebra/Equation/Equation.hpp>

namespace alba
{

namespace algebra
{

class SolutionToEquation
{
public:
    SolutionToEquation(Equation const& equation);

private:
    Equation m_equation;
};


}

}
