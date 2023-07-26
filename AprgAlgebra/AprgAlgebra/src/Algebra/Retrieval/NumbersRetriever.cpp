#include "NumbersRetriever.hpp"

namespace alba {

namespace algebra {

AlbaNumbersSet const& NumbersRetriever::getNumbers() const { return m_numbers; }

void NumbersRetriever::retrieveFromConstant(Constant const& constant) { m_numbers.emplace(constant.getNumber()); }

void NumbersRetriever::retrieveFromVariable(Variable const&) { m_numbers.emplace(1); }

void NumbersRetriever::retrieveFromMonomial(Monomial const& monomial) {
    m_numbers.emplace(monomial.getCoefficient());
    for (auto const& [variableName, exponent] : monomial.getVariablesToExponentsMap()) {
        m_numbers.emplace(exponent);
    }
}

}  // namespace algebra

}  // namespace alba
