#include "Equation.hpp"

using namespace std;

namespace alba
{

namespace algebra
{

Equation::Equation()
{}

Equation::Equation(
        std::string const& equationOperator,
        Term const& leftHandTerm,
        Term const& rightHandTerm)
     : m_equationOperator(equationOperator)
     , m_leftHandTerm(leftHandTerm)
     , m_rightHandTerm(rightHandTerm)
{}

bool Equation::operator==(Equation const& second) const
{
   return m_equationOperator == second.m_equationOperator
           && m_leftHandTerm == second.m_leftHandTerm
           && m_rightHandTerm == second.m_rightHandTerm;
}

bool Equation::operator!=(Equation const& second) const
{
   return !(operator==(second));
}

bool Equation::operator<(Equation const& second) const
{
    bool result(false);
    if(m_equationOperator == second.m_equationOperator)
    {
        if(m_leftHandTerm == second.m_leftHandTerm)
        {
            result = m_rightHandTerm < second.m_rightHandTerm;
        }
        else
        {
            result = m_leftHandTerm < second.m_leftHandTerm;
        }
    }
    else
    {
        result = m_equationOperator < second.m_equationOperator;
    }
    return result;
}

Operator const& Equation::getEquationOperator() const
{
    return m_equationOperator;
}

Term const& Equation::getLeftHandTerm() const
{
    return m_leftHandTerm;
}

Term const& Equation::getRightHandTerm() const
{
    return m_rightHandTerm;
}

string Equation::getDisplayableString() const
{
    return m_leftHandTerm.getDisplayableString()
            + " " + m_equationOperator.getDisplayableString()
            + " " + m_rightHandTerm.getDisplayableString();
}

ostream & operator<<(ostream & out, Equation const& equation)
{
    out << equation.getDisplayableString();
    return out;
}

}

}
