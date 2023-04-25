#include "LinearDiophantineEquationCoefficientSolver.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

using namespace alba::mathHelper;

namespace alba {

namespace algebra {

LinearDiophantineEquationCoefficientSolver::LinearDiophantineEquationCoefficientSolver(
    AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c)
    : m_solutionStatus(SolutionStatus::Unknown), m_x{}, m_y{}, m_a{}, m_b{}, m_c{}, m_gcfOfAAndB{} {
    solve(a, b, c);
}

bool LinearDiophantineEquationCoefficientSolver::isSolved() const { return SolutionStatus::Solved == m_solutionStatus; }

LinearDiophantineEquationCoefficientSolver::SolutionStatus
LinearDiophantineEquationCoefficientSolver::getSolutionStatus() const {
    return m_solutionStatus;
}

LinearDiophantineEquationCoefficientSolver::Integer LinearDiophantineEquationCoefficientSolver::getX() const {
    return m_x;
}

LinearDiophantineEquationCoefficientSolver::Integer LinearDiophantineEquationCoefficientSolver::getY() const {
    return m_y;
}

LinearDiophantineEquationCoefficientSolver::Integer LinearDiophantineEquationCoefficientSolver::getAnotherXValue(
    Integer const muliplier) const {
    return m_x + (muliplier * m_b / m_gcfOfAAndB);
}

LinearDiophantineEquationCoefficientSolver::Integer LinearDiophantineEquationCoefficientSolver::getAnotherYValue(
    Integer const muliplier) const {
    return m_y - (muliplier * m_a / m_gcfOfAAndB);
}

void LinearDiophantineEquationCoefficientSolver::solve(
    AlbaNumber const& aNumber, AlbaNumber const& bNumber, AlbaNumber const& cNumber) {
    if (aNumber.isIntegerType() && bNumber.isIntegerType() &&
        cNumber.isIntegerType())  // Each number in the equation has to be an integer.
    {
        m_a = aNumber.getInteger();
        m_b = bNumber.getInteger();
        m_c = cNumber.getInteger();

        if (m_c == 0) {
            m_solutionStatus = SolutionStatus::InfiniteSolutions;
        } else if (m_a == 0 && m_b == 0) {
            m_solutionStatus = SolutionStatus::NoSolution;
        } else {
            // A Diophantine equation can be solved if c is divisible by gcd(a,b), and otherwise it cannot be solved.
            Integer x, y;
            m_gcfOfAAndB = getGreatestCommonFactorWithLastValues(m_a, m_b, x, y);

            if (isDivisible(m_c, m_gcfOfAAndB)) {
                m_solutionStatus = SolutionStatus::Solved;
                m_x = x * m_c / m_gcfOfAAndB;
                m_y = y * m_c / m_gcfOfAAndB;
            } else {
                m_solutionStatus = SolutionStatus::CannotBeSolved;
            }
        }
    } else {
        m_solutionStatus = SolutionStatus::CannotBeSolved;
    }
}

}  // namespace algebra

}  // namespace alba
