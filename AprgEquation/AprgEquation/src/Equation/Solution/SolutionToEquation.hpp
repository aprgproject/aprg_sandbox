#pragma once

#include <Equation/Equation/Equation.hpp>

namespace alba
{

namespace equation
{

class SolutionToEquation
{
public:
    SolutionToEquation(Equation const& equationAsParameter);

private:
    Equation m_equation;
};


}

}
