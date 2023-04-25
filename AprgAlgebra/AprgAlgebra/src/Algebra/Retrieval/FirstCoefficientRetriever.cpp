#include "FirstCoefficientRetriever.hpp"

namespace alba {

namespace algebra {

FirstCoefficientRetriever::FirstCoefficientRetriever() : m_isValueSet(false) {}

void FirstCoefficientRetriever::retrieveFromConstant(Constant const& constant) {
    if (!m_isValueSet) {
        m_savedData = constant.getNumberConstReference();
        m_isValueSet = true;
    }
}

void FirstCoefficientRetriever::retrieveFromVariable(Variable const&) {
    if (!m_isValueSet) {
        m_savedData = 1;
        m_isValueSet = true;
    }
}

void FirstCoefficientRetriever::retrieveFromMonomial(Monomial const& monomial) {
    if (!m_isValueSet) {
        m_savedData = monomial.getConstantConstReference();
        m_isValueSet = true;
    }
}

}  // namespace algebra

}  // namespace alba
