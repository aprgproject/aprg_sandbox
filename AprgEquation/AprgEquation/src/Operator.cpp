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
