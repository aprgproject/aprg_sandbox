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
    void simplifyLeftHandSideAndRightHandSide(Term & leftHandSide, Term & rightHandSide);
    void raiseLeftHandSideAndRightHandSideToPowerIfLogarithmic(Term & leftHandSide, Term & rightHandSide);
    Term getNewCombinedTerm(Term const& leftHandSide, Term const& rightHandSide) const;
    void negateTermIfNeeded(Term & leftHandSide, std::string & equationOperatorString);
    void removeExponentIfNeeded( Term & leftHandSide);
    void completeExpressionWithFractionalExponentsIfNeeded(Term & leftHandSide);
    void simplifyLeftHandSide(Term & term);
    bool areTheSignsOfTwoTermsDifferent(TermWithDetails const& firstTerm, TermWithDetails const& secondTerm);

    Equation m_equation;
};
}

}

}
