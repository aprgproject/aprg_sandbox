#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>

namespace alba {

namespace algebra {

using BaseNumberOfTermsRetriever = BaseRetriever<int>;

class NumberOfTermsRetriever final : public BaseNumberOfTermsRetriever {
public:
    NumberOfTermsRetriever();
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    void retrieveFromExpression(Expression const& expression) override;
    void retrieveFromFunction(Function const& functionObject) override;
};

}  // namespace algebra

}  // namespace alba
