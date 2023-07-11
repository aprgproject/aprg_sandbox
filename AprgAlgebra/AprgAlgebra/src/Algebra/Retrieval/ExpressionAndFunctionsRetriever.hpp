#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

class ExpressionAndFunctionsRetriever final : public BaseRetriever {
public:
    TermSet const& getExpressionsAndFunctions() const;

    void retrieveFromPolynomial(Polynomial const&) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    TermSet m_expressionsAndFunctions;
};

}  // namespace algebra

}  // namespace alba
