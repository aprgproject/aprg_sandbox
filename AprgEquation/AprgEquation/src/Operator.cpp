#include "Operator.hpp"

#include <Utilities.hpp>

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

bool Operator::operator!=(Operator const& second) const
{
    return m_operatingString != second.m_operatingString;
}

bool Operator::operator<(Operator const& second) const
{
    return getOperatorPriority(m_operatingString) < getOperatorPriority(second.m_operatingString);
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

bool Operator::isAnOperatorThatCanPerformed() const
{
    return isAddition() || isSubtraction() || isMultiplication() || isDivision() || isRaiseToPower();
}

bool Operator::isOpeningGroupOperator() const
{
    return "(" == m_operatingString;
}

bool Operator::isClosingGroupOperator() const
{
    return ")" == m_operatingString;
}

OperatorLevel Operator::getOperatorLevel() const
{
    OperatorLevel result(OperatorLevel::Unknown);
    if(isAddition() || isSubtraction())
    {
        result = OperatorLevel::AdditionAndSubtraction;
    }
    else if(isMultiplication() || isDivision())
    {
        result = OperatorLevel::MultiplicationAndDivision;
    }
    else if(isRaiseToPower())
    {
        result = OperatorLevel::RaiseToPower;
    }
    return result;
}

string Operator::getOperatorString() const
{
    return m_operatingString;
}

string Operator::getDisplayableString() const
{
    return m_operatingString;
}

void Operator::setOperatorString(string const& operatingString)
{
    m_operatingString = operatingString;
}

}

}
