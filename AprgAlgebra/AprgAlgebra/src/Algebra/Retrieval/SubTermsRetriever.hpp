#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

using BaseSubTermsRetriever = BaseRetriever<TermSet>;

class SubTermsRetriever final : public BaseSubTermsRetriever {
public:
    SubTermsRetriever();

    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
};

}  // namespace algebra

}  // namespace alba
