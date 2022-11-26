#include "VariableTerm.hpp"

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <BooleanAlgebra/Term/Utilities/StringHelpers.hpp>

using namespace alba::mathHelper;
using namespace alba::stringHelper;
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
    : m_variableName(getStringWithoutStartingAndTrailingWhiteSpace(variableName))
    , m_isNegated(false)
{
    initialize();
}

VariableTerm VariableTerm::createNegatedVariableTerm(
        string const& variableName)
{
    VariableTerm result(variableName);
    result.negate();
    return result;
}

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

string VariableTerm::getVariableTermName() const
{
    return m_variableName;}

void VariableTerm::setVariableTermName(string const& variableName)
{
    m_variableName = variableName;
}

void VariableTerm::negate()
{
    m_isNegated = !m_isNegated;
}

void VariableTerm::initialize()
{
    int lastIndex = m_variableName.length()-1;
    int index=lastIndex;
    for(; index>=0; index--)
    {
        if(!isPrime(m_variableName.at(index)))
        {
            break;
        }
    }
    m_isNegated = isOdd(lastIndex-index);
    m_variableName.resize(index+1);
}

ostream & operator<<(ostream & out, VariableTerm const& variableTerm)
{
    out << variableTerm.m_variableName;
    if(variableTerm.m_isNegated)
    {
        out << "'";
    }
    return out;
}
}

}
