#include "Variable.hpp"

using namespace std;

namespace alba
{

namespace equation
{

Variable::Variable()
{}

Variable::Variable(string const& variableName)
    : m_variableName(variableName)
{}

bool Variable::operator==(Variable const& second) const
{
    return m_variableName == second.m_variableName;
}

bool Variable::operator!=(Variable const& second) const
{
    return m_variableName != second.m_variableName;
}

bool Variable::operator<(Variable const& second) const
{
    return m_variableName < second.m_variableName;
}

string Variable::getDisplayableString() const
{
    return m_variableName;
}

string Variable::getVariableName() const
{
    return m_variableName;
}

void Variable::setVariableName(string const& variableName)
{
    m_variableName = variableName;
}

}

}
