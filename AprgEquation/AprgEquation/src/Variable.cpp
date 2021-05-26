#include "Variable.hpp"

using namespace std;

namespace alba
{

namespace equation
{

Variable::Variable()
{}

Variable::Variable(const char* variableName)
    : m_variableName(variableName)
{}

Variable::Variable(string const& variableName)
    : m_variableName(variableName)
{}

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
