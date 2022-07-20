#include "VariableNamesRetriever.hpp"

namespace alba
{

namespace booleanAlgebra
{

void VariableNamesRetriever::retrieveFromVariableTerm(VariableTerm const& variableTerm)
{
    m_savedData.emplace(variableTerm.getVariableTermName());
}

}

}
