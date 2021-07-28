#include "BaseSolver.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

BaseSolver::BaseSolver()
    : m_isSolved(false)
    , m_isACompleteSolution(false)
{}

bool BaseSolver::isSolved() const
{
    return m_isSolved;
}

bool BaseSolver::isACompleteSolution() const
{
    return m_isACompleteSolution;
}

void BaseSolver::setAsCompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = true;
}

void BaseSolver::setAsIncompleteSolution()
{
    m_isSolved = true;
    m_isACompleteSolution = false;
}

}

}
