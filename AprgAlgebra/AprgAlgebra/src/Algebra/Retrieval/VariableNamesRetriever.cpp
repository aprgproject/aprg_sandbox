#include "VariableNamesRetriever.hpp"

namespace alba {

namespace algebra {

VariableNamesSet const& VariableNamesRetriever::getVariableNames() const { return m_variableNames; }

VariableNamesSet& VariableNamesRetriever::getVariableNamesReference() { return m_variableNames; }

void VariableNamesRetriever::retrieveFromVariable(Variable const& variable) {
    m_variableNames.emplace(variable.getVariableName());
}

void VariableNamesRetriever::retrieveFromMonomial(Monomial const& monomial) {
    for (auto const& variableExponentsPair : monomial.getVariablesToExponentsMap()) {
        m_variableNames.emplace(variableExponentsPair.first);
    }
}

}  // namespace algebra

}  // namespace alba
