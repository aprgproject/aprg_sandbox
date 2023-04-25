#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

using BaseExpressionAndFunctionsRetriever = BaseRetriever<TermSet>;

class ExpressionAndFunctionsRetriever final : public BaseExpressionAndFunctionsRetriever {
public:
    ExpressionAndFunctionsRetriever();
    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
};

}  // namespace algebra

}  // namespace alba
