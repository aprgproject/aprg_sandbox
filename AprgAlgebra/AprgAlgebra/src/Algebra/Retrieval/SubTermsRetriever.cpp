#include "SubTermsRetriever.hpp"

namespace alba {

namespace algebra {

SubTermsRetriever::SubTermsRetriever() {}

void SubTermsRetriever::retrieveFromConstant(Constant const& constant) { m_savedData.emplace(Term(constant)); }

void SubTermsRetriever::retrieveFromVariable(Variable const& variable) { m_savedData.emplace(Term(variable)); }

void SubTermsRetriever::retrieveFromMonomial(Monomial const& monomial) { m_savedData.emplace(Term(monomial)); }

void SubTermsRetriever::retrieveFromPolynomial(Polynomial const& polynomial) { m_savedData.emplace(Term(polynomial)); }

void SubTermsRetriever::retrieveFromExpression(Expression const& expression) {
    m_savedData.emplace(Term(expression));
    BaseSubTermsRetriever::retrieveFromExpression(expression);
}

void SubTermsRetriever::retrieveFromFunction(Function const& functionObject) {
    m_savedData.emplace(Term(functionObject));
    BaseSubTermsRetriever::retrieveFromFunction(functionObject);
}

}  // namespace algebra

}  // namespace alba
