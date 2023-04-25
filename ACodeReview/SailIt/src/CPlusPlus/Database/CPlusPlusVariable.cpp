#include "CPlusPlusVariable.hpp"

namespace codeReview {

CPlusPlusVariable::CPlusPlusVariable() : m_type() {}

CPlusPlusVariable::CPlusPlusVariable(CPlusPlusType const& cPlusPlusType) : m_type(cPlusPlusType) {}

CPlusPlusType CPlusPlusVariable::getType() const { return m_type; }

}  // namespace codeReview
