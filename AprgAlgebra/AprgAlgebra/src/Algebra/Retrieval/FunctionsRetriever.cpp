#include "FunctionsRetriever.hpp"

namespace alba {

namespace algebra {

FunctionsRetriever::FunctionsRetriever(FunctionCondition const& isFunctionIncluded)
    : m_isFunctionIncluded(isFunctionIncluded) {}

FunctionsSet const& FunctionsRetriever::getFunctions() const { return m_functions; }

void FunctionsRetriever::retrieveFromPolynomial(Polynomial const&) {}

void FunctionsRetriever::retrieveFromFunction(Function const& functionObject) {
    if (m_isFunctionIncluded(functionObject)) {
        m_functions.emplace(functionObject);
    }
}

}  // namespace algebra

}  // namespace alba
