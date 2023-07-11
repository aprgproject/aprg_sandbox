#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>

namespace alba {

namespace algebra {

class NumberOfTermsRetriever final : public BaseRetriever {
public:
    NumberOfTermsRetriever();

    int getNumberOfTerms() const;
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;

private:
    int m_numberOfTerms;
};

}  // namespace algebra

}  // namespace alba
