#include "VariableTerm.hpp"

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

VariableTerm::VariableTerm()
    : m_variableName()
    , m_isNegated(false)
{}

VariableTerm::VariableTerm(string const& variableName)
    : m_variableName(variableName)
    , m_isNegated(false)
{}

VariableTerm::VariableTerm(string const& variableName, bool const isNegated)
    : m_variableName(variableName)
    , m_isNegated(isNegated)
{}

bool VariableTerm::operator==(VariableTerm const& second) const
{
    return m_variableName == second.m_variableName && m_isNegated == second.m_isNegated;
}

bool VariableTerm::operator!=(VariableTerm const& second) const
{
    return !operator==(second);
}

bool VariableTerm::operator<(VariableTerm const& second) const
{
    bool result(false);
    if(m_variableName != second.m_variableName)
    {
        result = m_variableName < second.m_variableName;
    }
    else
    {
        result = m_isNegated < second.m_isNegated;
    }
    return result;
}

VariableTerm VariableTerm::operator~() const
{
    VariableTerm result(*this);
    result.negate();
    return result;
}

bool VariableTerm::isNegated() const
{
    return m_isNegated;
}

string VariableTerm::getDisplayableString() const
{
    string result(m_variableName);
    if(m_isNegated)
    {
        result += "'";
    }
    return result;
}

string VariableTerm::getVariableTermName() const
{
    return m_variableName;
}

void VariableTerm::setVariableTermName(string const& variableName)
{
    m_variableName = variableName;
}

void VariableTerm::negate()
{
    m_isNegated = !m_isNegated;
}

ostream & operator<<(ostream & out, VariableTerm const& variableTerm)
{
    out << variableTerm.getDisplayableString();
    return out;
}

}

}
