#include "NumbersRetriever.hpp"

namespace alba
{

namespace algebra
{

void NumbersRetriever::retrieveFromConstant(Constant const& constant)
{
    m_savedData.emplace(constant.getNumberConstReference());
}

void NumbersRetriever::retrieveFromVariable(Variable const&)
{
    m_savedData.emplace(1);
}

void NumbersRetriever::retrieveFromMonomial(Monomial const& monomial)
{
    m_savedData.emplace(monomial.getConstantConstReference());
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        m_savedData.emplace(variableExponentsPair.second);
    }
}

}

}
