#include "ExpressionAndFunctionsRetriever.hpp"

namespace alba {

namespace algebra {

ExpressionAndFunctionsRetriever::ExpressionAndFunctionsRetriever() {}

void ExpressionAndFunctionsRetriever::retrieveFromPolynomial(Polynomial const&) {}

void ExpressionAndFunctionsRetriever::retrieveFromExpression(Expression const& expression) {
    m_savedData.emplace(Term(expression));
    BaseExpressionAndFunctionsRetriever::retrieveFromExpression(expression);
}

void ExpressionAndFunctionsRetriever::retrieveFromFunction(Function const& functionObject) {
    m_savedData.emplace(Term(functionObject));
    BaseExpressionAndFunctionsRetriever::retrieveFromFunction(functionObject);
}

}  // namespace algebra

}  // namespace alba
