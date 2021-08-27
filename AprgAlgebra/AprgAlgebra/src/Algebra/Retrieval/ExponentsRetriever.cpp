#include "ExponentsRetriever.hpp"

namespace alba
{

namespace algebra
{

void ExponentsRetriever::retrieveFromConstant(Constant const&)
{
    //m_savedData.emplace(0); // don't consider constant have exponent 0
}

void ExponentsRetriever::retrieveFromVariable(Variable const&)
{
   // m_savedData.emplace(1); // don't consider variable have exponent 1
}

void ExponentsRetriever::retrieveFromMonomial(Monomial const& monomial)
{
    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        m_savedData.emplace(variableExponentsPair.second);
    }
}

}

}
