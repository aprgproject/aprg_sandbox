#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Algebra/Term/TermTypes/TermContainerTypes.hpp>

namespace alba {

namespace algebra {

class SubTermsRetriever final : public BaseRetriever {
public:
    SubTermsRetriever();

    TermSet const& getSubTerms() const;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromPolynomial(Polynomial const& polynomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    TermSet m_subTerms;
};

}  // namespace algebra

}  // namespace alba
