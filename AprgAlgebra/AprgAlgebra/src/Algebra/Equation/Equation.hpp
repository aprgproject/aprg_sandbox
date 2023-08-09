#pragma once

#include <Algebra/Equation/EquationOperator.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class Equation
{
public:
    Equation();
    Equation(
            Term const& leftHandTerm,
            std::string const& equationOperator,
            Term const& rightHandTerm);

    bool operator==(Equation const& second) const;
    bool operator!=(Equation const& second) const;
    bool operator<(Equation const& second) const;

    EquationOperator const& getEquationOperator() const;
    Term const& getLeftHandTerm() const;
    Term const& getRightHandTerm() const;
    std::string getDisplayableString() const;

private:
    EquationOperator m_equationOperator;
    Term m_leftHandTerm;
    Term m_rightHandTerm;
};

std::ostream & operator<<(std::ostream & out, Equation const& equation);

}

}
