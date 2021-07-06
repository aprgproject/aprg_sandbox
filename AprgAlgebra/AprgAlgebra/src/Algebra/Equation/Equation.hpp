#pragma once

#include <Algebra/Term/Term.hpp>
#include <Algebra/Term/Operator.hpp>

#include <string>

namespace alba
{

namespace algebra
{

class Equation
{
    friend std::ostream & operator<<(std::ostream & out, Equation const& constant);
public:
    Equation();
    Equation(
            std::string const& equationOperator,
            Term const& leftHandTerm,
            Term const& rightHandTerm);

    bool operator==(Equation const& second) const;
    bool operator!=(Equation const& second) const;
    bool operator<(Equation const& second) const;

    Operator const& getEquationOperator() const;
    Term const& getLeftHandTerm() const;
    Term const& getRightHandTerm() const;
    std::string getDisplayableString() const;

private:
    Operator m_equationOperator;
    Term m_leftHandTerm;
    Term m_rightHandTerm;
};

std::ostream & operator<<(std::ostream & out, Equation const& equation);

}

}