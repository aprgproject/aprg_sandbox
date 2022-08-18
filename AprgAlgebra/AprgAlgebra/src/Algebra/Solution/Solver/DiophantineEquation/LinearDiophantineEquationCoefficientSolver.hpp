#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace algebra
{


class LinearDiophantineEquationCoefficientSolver
{
public:
    // A Linear Diophantine Equation is an equation of the form ax+by = c

    using Integer = long long int;

    enum class SolutionStatus
    {
        Unknown,
        CannotBeSolved,
        InfiniteSolutions,
        NoSolution,
        Solved
    };

    LinearDiophantineEquationCoefficientSolver(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

    bool isSolved() const;

    SolutionStatus getSolutionStatus() const;
    Integer getX() const;
    Integer getY() const;

private:
    Integer getGcfWithBackTracking(Integer const a, Integer const b, Integer& x, Integer& y);
    void solve(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);
    SolutionStatus m_solutionStatus;
    Integer m_x;
    Integer m_y;
};

}

}
