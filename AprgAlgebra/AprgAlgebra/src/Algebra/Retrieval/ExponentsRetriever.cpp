#include "ExponentsRetriever.hpp"

namespace alba {

namespace algebra {

AlbaNumbersSet const& ExponentsRetriever::getExponents() const { return m_exponents; }

void ExponentsRetriever::retrieveFromMonomial(Monomial const& monomial) {
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        m_exponents.emplace(exponent);
    }
}
}  // namespace algebra

}  // namespace alba