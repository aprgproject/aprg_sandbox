#include "ExponentsRetriever.hpp"

namespace alba {

namespace algebra {

AlbaNumbersSet const& ExponentsRetriever::getExponents() const { return m_exponents; }

void ExponentsRetriever::retrieveFromMonomial(Monomial const& monomial) {
    for (auto const& variableExponentsPair : monomial.getVariablesToExponentsMap()) {
        m_exponents.emplace(variableExponentsPair.second);
    }
}
}  // namespace algebra

}  // namespace alba