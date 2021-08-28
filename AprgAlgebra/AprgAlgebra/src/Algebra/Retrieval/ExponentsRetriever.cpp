#include "ExponentsRetriever.hpp"

namespace alba
{

namespace algebra
{

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
