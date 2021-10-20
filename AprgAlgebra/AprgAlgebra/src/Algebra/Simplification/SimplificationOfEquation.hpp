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
    Term getNewCombinedTerm(Equation const& equation) const;
    void negateTermIfNeeded(
            Term & leftHandSide,
            std::string & equationOperatorString);
    void removeExponentIfNeeded(
            Term & leftHandSide);
    void completeExpressionWithFractionalExponentsIfNeeded(
            Term & leftHandSide);
    void simplifyLeftHandTerm(
            Term & term);
    bool areTheSignsOfTwoTermsDifferent(
            TermWithDetails const& firstTerm,
            TermWithDetails const& secondTerm);

    Equation m_equation;
};
}

}
}
