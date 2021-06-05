#include "Operator.hpp"

using namespace std;

namespace alba
{

namespace equation
{

Operator::Operator()
{}

Operator::Operator(string const& operatingString)
    : m_operatingString(operatingString)
{}

bool Operator::operator==(Operator const& second) const
{
    return m_operatingString == second.m_operatingString;
}

bool Operator::isAddition() const
{
    return "+" == m_operatingString;
}

bool Operator::isSubtraction() const
{
    return "-" == m_operatingString;
}

bool Operator::isMultiplication() const
{
    return "*" == m_operatingString;
}

bool Operator::isDivision() const
{
    return "/" == m_operatingString;
}

bool Operator::isRaiseToPower() const
{
    return "^" == m_operatingString;
}

string Operator::getOperatorString() const
{
    return m_operatingString;
}

void Operator::setOperatorString(string const& operatingString)
{
    m_operatingString = operatingString;
}

}

}
