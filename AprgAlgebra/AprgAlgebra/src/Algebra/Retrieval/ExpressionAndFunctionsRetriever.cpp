#include "ExpressionAndFunctionsRetriever.hpp"

namespace alba {

namespace algebra {

TermSet const& ExpressionAndFunctionsRetriever::getExpressionsAndFunctions() const { return m_expressionsAndFunctions; }

void ExpressionAndFunctionsRetriever::retrieveFromPolynomial(Polynomial const&) {}

void ExpressionAndFunctionsRetriever::retrieveFromExpression(Expression const& expression) {
    m_expressionsAndFunctions.emplace(Term(expression));
    BaseRetriever::retrieveFromExpression(expression);
}

void ExpressionAndFunctionsRetriever::retrieveFromFunction(Function const& functionObject) {
    m_expressionsAndFunctions.emplace(Term(functionObject));
    BaseRetriever::retrieveFromFunction(functionObject);
}

}  // namespace algebra

}  // namespace alba
