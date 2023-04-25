#include "ExponentsRetriever.hpp"

namespace alba {

namespace algebra {

void ExponentsRetriever::retrieveFromMonomial(Monomial const& monomial) {
    for (auto const& variableExponentsPair : monomial.getVariablesToExponentsMapConstReference()) {
        m_savedData.emplace(variableExponentsPair.second);
    }
}

}  // namespace algebra

}  // namespace alba
