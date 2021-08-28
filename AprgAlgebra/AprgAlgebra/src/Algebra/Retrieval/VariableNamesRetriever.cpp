#include "VariableNamesRetriever.hpp"

namespace alba
{

namespace algebra
{

void VariableNamesRetriever::retrieveFromVariable(Variable const& variable)
{
    m_savedData.emplace(variable.getVariableName());}

void VariableNamesRetriever::retrieveFromMonomial(Monomial const& monomial)
{    for(Monomial::VariableExponentPair const& variableExponentsPair
        : monomial.getVariablesToExponentsMapConstReference())
    {
        m_savedData.emplace(variableExponentsPair.first);
    }
}

}

}
