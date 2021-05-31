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

AlbaNumber Operator::performOperation(AlbaNumber const& number1, AlbaNumber const& number2) const
{
    AlbaNumber result;
    if(isAddition())
    {
        result = number1 + number2;
    }
    else if(isSubtraction())
    {
        result = number1 - number2;
    }
    else if(isMultiplication())
    {
        result = number1 * number2;
    }
    else if(isDivision())
    {
        result = number1 / number2;
    }
    else if(isRaiseToPower())
    {
        result = number1 ^ number2;
    }
    return result;
}

void Operator::setOperatorString(string const& operatingString)
{
    m_operatingString = operatingString;}

}

}